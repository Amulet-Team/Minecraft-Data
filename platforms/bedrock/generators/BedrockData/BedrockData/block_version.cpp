#pragma once
#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include "get_file.hpp"


THook(void, "?prepareBlocks@BlockTypeRegistry@@SAXI@Z", unsigned int version) {
    *getFile("generated/block/version.txt") << version << std::endl;
    original(version);
}
