#pragma once

#include <string>
#include <PRISM/Renderer/Mesh.h>

class FLoader
{
public:
    static std::string LoadFile(const std::string& path);
    static Mesh LoadObject(const std::string &path);
};