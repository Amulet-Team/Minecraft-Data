#pragma once
#include "pch.h"

#include <fstream>
#include <string>

std::ofstream* getFile(std::string path, bool binary = false);
