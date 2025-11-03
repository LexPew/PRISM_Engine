#include <PRISM/Renderer/Texture.h>
#include <glad/glad.h>
#include <PRISM/Core/AssetManger.h>


// Helper functions for eum conversion, trying to avoid as much opengl in the header or outside of renderer
// TODO: Try apply this logic to more places
static GLenum ToGLWrap(Wrap wrap)
{
    switch (wrap)
    {
    case Wrap::Repeat:
        return GL_REPEAT;
    case Wrap::Mirrored_Repeat:
        return GL_MIRRORED_REPEAT;
    case Wrap::Clamp:
        return GL_CLAMP_TO_EDGE;
    default:
        return GL_REPEAT;
    }
}

static GLenum ToGLFilter(Filter filter)
{
    switch (filter)
    {
    case Filter::Linear:
        return GL_LINEAR;
    case Filter::Nearest:
        return GL_NEAREST;
    default:
        return GL_LINEAR;
    }
}

void Texture::Initialize(const ImageData &texture)
{
    if (textureID != 0)
        return;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ToGLFilter(textureFilter));

    if (texture.data)
    {

        GLenum format = GL_RGBA;
        if (texture.channels == 3)
            format = GL_RGB;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            texture.width,
            texture.height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            texture.data);

        if (mipmaps)
            glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Always unbind
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<Texture> Texture::CreateDefault()
{
    
    return AssetManager::LoadTexture("engine/textures/default_texture.png");
}
Texture::~Texture()
{
    if (textureID != 0)
    {
        glDeleteTextures(1, &textureID);
    }
}
void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

