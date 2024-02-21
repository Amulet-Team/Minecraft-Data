#pragma once

#include <fstream>
#include <map>
#include <string>
#include <filesystem>
#include <mutex>
#include <thread>
#include <iostream>
#include <type_traits>
#include "logging.hpp"


std::map<std::string, bool> _opened;
std::map<std::string, std::mutex> _locks;


void logToBinaryFile(std::string path, std::string data) {
    std::mutex& lock = _locks[path];
    std::lock_guard<std::mutex> guard(lock);
    std::string dir_s = path.substr(0, path.rfind("/"));
    std::wstring dir = std::wstring(dir_s.begin(), dir_s.end());
    std::filesystem::create_directories(dir_s);

    std::ofstream file;
    if (_opened[path]) {
        // If the file has been opened this session we just want to append to it.
        file.open(path, std::ios::out | std::ios::app | std::ios::binary);
    }
    else {
        // If the file hasn't been opened this session we must trucate it
        file.open(path, std::ios::out | std::ios::binary);
        _opened[path] = true;
    }
    file.write(data.c_str(), data.size());
    file.close();
}


void logToFile(std::string path, std::string msg) {
    std::mutex& lock = _locks[path];
    std::lock_guard<std::mutex> guard(lock);
    std::string dir_s = path.substr(0, path.rfind("/"));
    std::wstring dir = std::wstring(dir_s.begin(), dir_s.end());
    std::filesystem::create_directories(dir_s);

    std::ofstream file;
    if (_opened[path]) {
        // If the file has been opened this session we just want to append to it.
        file.open(path, std::ios::out | std::ios::app);
    }
    else {
        // If the file hasn't been opened this session we must trucate it
        file.open(path);
        _opened[path] = true;
    }
    file << msg << std::endl;
    file.close();
}


void debug(std::string msg) {
    std::cout << msg << std::endl;
    logToFile("log/debug.txt", msg);
}
