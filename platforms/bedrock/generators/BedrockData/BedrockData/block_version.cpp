#pragma once
#include "pch.h"

#include <MC/HashedString.hpp>
#include "get_file.hpp"


THook(void, "?prepareBlocks@BlockTypeRegistry@@SAXI@Z", unsigned int version) {
    *getFile("generated/block/version.txt") << version << std::endl;
    original(version);
}


void block_version() {
    if (dlsym("?prepareBlocks@BlockTypeRegistry@@SAXI@Z") == NULL) {
        *getFile("generated/err.txt") << "?prepareBlocks@BlockTypeRegistry@@SAXI@Z" << std::endl;
    }
}
