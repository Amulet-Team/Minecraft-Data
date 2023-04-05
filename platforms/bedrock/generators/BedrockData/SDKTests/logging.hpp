#pragma once

#include <fstream>
#include <map>
#include <string>
#include <filesystem>
#include <mutex>
#include <thread>
#include <iostream>
#include <type_traits>


void logToFile(std::string path, std::string msg);


template <typename T>
    requires std::is_arithmetic_v<T>
void logToFile(std::string path, T msg) {
    std::string msg_str = std::to_string(msg);
    logToFile(path, msg_str);
}
