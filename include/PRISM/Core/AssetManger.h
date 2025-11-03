#pragma once

// Supported File Types
#include <PRISM/Renderer/Texture.h>
#include <PRISM/Renderer/Mesh.h>
#include <PRISM/Utils/FLoader.h>
#include <memory>
#include <unordered_map>
#include <string>

class AssetManager
{
private:
    inline static std::unordered_map<std::string, std::weak_ptr<Texture>> textures;
    inline static std::unordered_map<std::string, std::weak_ptr<Mesh>> meshes;

public:
    // Mesh Loading
    static std::shared_ptr<Mesh> LoadMesh(const std::string &relativePath)
    {
        // Try find the mesh entry
        std::string fullPath = FLoader::GetAssetPath(relativePath);
        auto meshEntry = meshes.find(fullPath);

        // If meshEntry does exist
        if (meshEntry != meshes.end())
        {
            // Since entry exists we check if the smart pointer is still valid via lock
            // this will either return the smart pointer or nullptr which if(meshPtr) aka
            // if valid then we return otherwise we can load the asset new
            if (auto meshPtr = meshEntry->second.lock())
            {
                return meshPtr;
            }
        }
        // Load a fresh one
        auto mesh = FLoader::LoadObject(fullPath);
        meshes[fullPath] = mesh;
        return mesh;
    };
    // Texture Loading
    static std::shared_ptr<Texture> LoadTexture(const std::string &relativePath)
    {
        // Try find texture entry
        std::string fullPath = FLoader::GetAssetPath(relativePath);
        auto textureEntry = textures.find(fullPath);

        if (textureEntry != textures.end())
        {
            if (auto texturePtr = textureEntry->second.lock())
            {
                return texturePtr;
            }
        }
        auto loadedTexture = FLoader::LoadImage(fullPath);
        auto texture = std::make_shared<Texture>(std::move(loadedTexture));
        textures[fullPath] = texture;
        return texture;
    }
};