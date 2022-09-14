#include "pch.h"

#include <fileapi.h>
#include <fstream>
#include <map>
#include <string>


std::map<std::string, std::ofstream> _files;

std::ofstream* getFile(std::string path, bool binary = false) {
    std::ofstream* file = &_files[path];
    if (!file->is_open()) {
        std::string dir_s = path.substr(0, path.rfind("/"));
        std::wstring dir = std::wstring(dir_s.begin(), dir_s.end());
        CreateDirectory(dir.c_str(), NULL);
        if (binary) {
            file->open(path, std::ios::binary);
        }
        else {
            file->open(path);
        }
    }
    return file;
}
