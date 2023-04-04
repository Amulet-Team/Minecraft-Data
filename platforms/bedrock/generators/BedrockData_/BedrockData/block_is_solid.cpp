#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_solid(const Block_* block) {
    typedef bool(*isSolidT)(const Block_*);
    auto isSolid = (isSolidT)dlsym("?isSolid@Block@@QEBA_NXZ");
    if (isSolid != NULL) {
        *getFile("generated/block/data/solid.txt") << isSolid(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isSolid@Block@@QEBA_NXZ" << std::endl;
    }
}
