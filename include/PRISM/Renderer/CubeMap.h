#pragma once
#include <PRISM/Renderer/Texture.h>

class CubeMap : public Texture
{
public:
    CubeMap(const ImageData &p_texture) : Texture()
    {
        Initialize(p_texture);
    };
    virtual void Initialize(const ImageData &texture) override;

    virtual void Bind() override;

};