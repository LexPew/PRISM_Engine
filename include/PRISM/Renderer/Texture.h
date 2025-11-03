#pragma once
#include <PRISM/Utils/FLoader.h>
// TODO: Add support for clamp to border
enum class Wrap { Repeat, Mirrored_Repeat, Clamp };
enum class Filter { Linear, Nearest };
class Texture
{
private:
    unsigned int textureID{0};    // GL Texture ID
    Wrap textureWrap{Wrap::Repeat};     // How image is wrapped, defaults to Repeat
    Filter textureFilter{Filter::Linear}; // How the image is filtered, default to Linear

    bool mipmaps{true};             // Whether mipmaps should be generated, default to true
 

    void Initialize(const ImageData &texture);

public:
    static std::shared_ptr<Texture> CreateDefault();
    Texture(const ImageData &p_texture)
    {
        Initialize(p_texture);
    };
    Texture(const ImageData &p_texture, Wrap p_textureWrap, Filter p_textureFiltering, bool p_generateMipMaps)
        : textureWrap(p_textureWrap), textureFilter(p_textureFiltering), mipmaps(p_generateMipMaps)
    {
        Initialize(p_texture);
    };

    ~Texture();
    
    unsigned int GetTextureID(){return textureID;}
    void Bind();


};