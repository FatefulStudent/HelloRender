#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace FileHelper
{
std::string ReadFile(const std::string& Path);
std::string GetExtensionFromFileName(const std::string& FileName);
}  // namespace FileHelper

#endif  // !FILE_HELPER_H
