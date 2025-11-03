#pragma once

#include <string>
#include <filesystem>
#include <PRISM/Renderer/Mesh.h>
#include <memory>
#include <stb_image/stb_image.h>

// Used to ensure RAII
struct ImageData
{
    unsigned char *data = nullptr;
    int width = 0;
    int height = 0;
    int channels = 0;
    ~ImageData()
    {
        if (data)
        {
            stbi_image_free(data);
        }
    }
};

class FLoader
{
public:
    static std::string LoadFile(const std::string &path);
    static std::shared_ptr<Mesh> LoadObject(const std::string &path);
    static ImageData LoadImage(const std::string &path);
    static std::string GetAssetPath(const std::string& relativePath){return (std::filesystem::path(ASSET_DIR) / relativePath).string();};
};