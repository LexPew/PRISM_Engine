#include <PRISM/Utils/FLoader.h>

#include <fstream>
#include <sstream>
#include <fmt/core.h>

std::string FLoader::LoadFile(const std::string& path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        fmt::println("FLoader Error: Failed to open file {}", path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}