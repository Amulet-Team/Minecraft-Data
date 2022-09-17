#include "pch.h"

#include <fstream>
#include <map>
#include <string>
#include <filesystem>


std::map<std::string, std::ofstream> _files;

std::ofstream* getFile(std::string path, bool binary = false) {
    std::ofstream* file = &_files[path];
    if (!file->is_open()) {
        std::string dir_s = path.substr(0, path.rfind("/"));
        std::wstring dir = std::wstring(dir_s.begin(), dir_s.end());
        std::filesystem::create_directories(dir_s);
        if (binary) {
            file->open(path, std::ios::binary);
        }
        else {
            file->open(path);
        }
    }
    return file;
}
