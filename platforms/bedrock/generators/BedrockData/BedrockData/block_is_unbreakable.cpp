#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_unbreakable(const Block_* block) {
    typedef bool(*isUnbreakableT)(const Block_*);
    auto isUnbreakable = (isUnbreakableT)dlsym("?isUnbreakable@Block@@QEBA_NXZ");
    if (isUnbreakable != NULL) {
        *getFile("generated/block/data/unbreakable.txt") << isUnbreakable(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isUnbreakable@Block@@QEBA_NXZ" << std::endl;
    }
}
