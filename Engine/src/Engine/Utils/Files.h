#pragma once

#include <string>

namespace MyEngine
{
    // Get string after last "." in file name
    std::string GetFileExtension(const std::string& fileName);
}
