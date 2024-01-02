#include "pch.h"

#include "Files.h"

namespace MyEngine
{
    std::string GetFileExtension(const std::string& fileName)
    {
        size_t dotPos = fileName.find_last_of(".");
        if (dotPos != std::string::npos)
        {
            return fileName.substr(dotPos + 1);
        }
        return fileName; // Full string if no extension found
    }
}
