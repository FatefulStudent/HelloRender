#include "FileHelper.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string FileHelper::ReadFile(const std::string& Path) {
    std::ifstream Input;
    Input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream StringStream;
    try {
        Input.open(Path);
        StringStream << Input.rdbuf();
        Input.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::FileHelper::FILE_NOT_SUCCESFULLY_READ: \"" << Path
                  << "\":" << e.what() << std::endl;
        throw -1;
    }
    const std::string result = StringStream.str();

    if (result.empty()) {
        std::cerr << "ERROR::FileHelper::File Is Empty: \"" << Path
                  << std::endl;
        throw -1;
    }
    return result;
}

std::string FileHelper::GetExtensionFromFileName(const std::string& FileName) {
    size_t ExtensionStartIndex = FileName.rfind(".");
    if (ExtensionStartIndex == std::string::npos)
        return {};

    // Actually extension starts after the dot
    ExtensionStartIndex += 1;

    // if the dot was the last char in path then it has no extension
    if (ExtensionStartIndex == FileName.length())
        return {};

    const std::string ExtensionSubstring =
        FileName.substr(ExtensionStartIndex);
    return ExtensionSubstring;
}
