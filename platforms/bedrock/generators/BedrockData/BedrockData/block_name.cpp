#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_name(const Block_* block) {
    typedef HashedString_ const &(*getNameT)(const Block_*);
    auto getName = (getNameT)dlsym("?getName@Block@@QEBAAEBVHashedString@@XZ");
    if (getName != NULL) {
        *getFile("generated/block/data/name.txt") << getName(block).getString() << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getName@Block@@QEBAAEBVHashedString@@XZ" << std::endl;
    }
}
