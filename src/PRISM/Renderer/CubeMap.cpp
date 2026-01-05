#include <PRISM/Renderer/CubeMap.h>
#include <glad/glad.h>
#include <fmt/core.h>

void CubeMap::Initialize(const ImageData &texture)
{
    // Return immediately if the texture is already initialized
    if (textureID != 0)
        return;

    // Update wrap type to clamp
    textureWrap = Wrap::Clamp;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Split the input texture into 6 faces, stored in a vector. We accomplish this by calculating the offsets for each face in the input texture.

    // Since we need the loaded images in a certain order we need a map, as currently they come in,
    // top,left,front,right,back,bottom and we need right,left,top,bottom,back,front due to opengls order when incrementing GL_TEXTURE_CUBE_MAP_POSITIVE_X++

    const int indexMap[6] = {2, 1, 4, 0, 5, 3};

    // This holds our face data temporarily
    std::vector<unsigned char *> facesData(6, nullptr);

    int imageWidth = texture.width / 4;
    int imageHeight = texture.height / 3;
    // Load each face of the cube map

    int faceIndex = 0;
    // For the first and second row we only need the second column as the rest are blank, only the middle row has 4 colunmns
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            // If we are in the first or last row only process the middle column
            if (row == 0 || row == 2)
            {
                if (col != 1)
                    continue;
            }

            int channels = texture.channels;
            int bytesPerPixel = channels;
            int bytesPerRow = texture.width * channels; //Full Row
            int bytesPerImageX = imageWidth * channels; //Single Image

            //We allocate a buffer with memory sized the image width * image height * channels, so if ours is 512x512 and rgba its about 1mb
            unsigned char* faceBuffer = new unsigned char[imageWidth * imageHeight * channels];

            //We now need to find the very first byte in our sub image,
            //first we get the position of the first byte of our overall texture in memory,
            //then we need to account for the row so we move down the size of an entire row 
            unsigned char* startingBytePosition = texture.data +
            (row * imageHeight * (bytesPerRow)) + //This moves us by the full rows
            (col * imageWidth * channels); //This is far simple as we only need to accound for col * imagewidth in bytes

            //Copy row by row, i cant even remember how this works fully
            for(int y = 0; y < imageHeight; y++){
                unsigned char* src = startingBytePosition + y * bytesPerRow;
                unsigned char* dst = faceBuffer + y * bytesPerImageX;

                memcpy(dst,src,bytesPerImageX);
            }
            facesData[indexMap[faceIndex]] = faceBuffer;
            ++faceIndex;
        }
    }

    // Now upload each face to the GPU
    GLenum format = GL_RGB;
    if (texture.channels == 4)
        format = GL_RGBA;
    else if (texture.channels == 1)
        format = GL_RED;

    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            format,
            imageWidth,
            imageHeight,
            0,
            format,
            GL_UNSIGNED_BYTE,
            facesData[i]);
    }

    // Cube map params
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLenum)ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLenum)ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLenum)ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLenum)ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLenum)ToGLWrap(textureWrap));

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

// JAMIE TEST
/*void CubeMap::Initialize(const ImageData &texture)
{
    // Return immediately if the texture is already initialized
    if (textureID != 0)
        return;
       //Test cubemap by setting each face to the same image
       const ImageData &faceImage = FLoader::LoadImage(FLoader::GetAssetPath("examples/custom_hmap.png"));
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    GLenum format = GL_RGB;
    if (faceImage.channels == 4)
        format = GL_RGBA;
    else if(faceImage.channels == 3){
        format = GL_RGB;
    }

    for(unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            format,
            faceImage.width,
            faceImage.height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            faceImage.data);
    }
    // Cube map params
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLenum)ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLenum)ToGLFilter(textureFilter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLenum)ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLenum)ToGLWrap(textureWrap));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLenum)ToGLWrap(textureWrap));
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


}*/
void CubeMap::Bind()
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}