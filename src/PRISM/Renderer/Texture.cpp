#include <PRISM/Renderer/Texture.h>
#include <glad/glad.h>
#include <PRISM/Core/AssetManger.h>
#include <fmt/core.h>
// Helper functions for OpenGL texture parameters conversion
unsigned int Texture::ToGLWrap(Wrap wrap)
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

unsigned int Texture::ToGLFilter(Filter filter)
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
    // Return immediately if the texture is already initialized
    if (textureID != 0)
        return;

    // Generate a new OpenGL texture ID and bind it
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping parameters //TODO: Find a way around the glenum and protected thingy
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)ToGLWrap(textureWrap));

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)ToGLFilter(textureFilter));

    // Load the texture data into OpenGL
    if (texture.data)
    {
        GLenum format = (texture.channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.data);

        // Generate mipmaps if requested
        if (mipmaps)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    // Unbind the texture to avoid any accidental modifications
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<Texture> Texture::CreateDefault()
{
    return AssetManager::LoadTexture("engine/textures/default_texture.png");
}

Texture::~Texture()
{
    // Destructor to clean up OpenGL resources when the texture object is destroyed
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
