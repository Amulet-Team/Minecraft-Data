#pragma once

#include <fstream>
#include <string>

std::ofstream* getFile(std::string path, bool binary = false);
