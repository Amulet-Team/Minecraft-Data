#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_friction(const Block_* block) {
    typedef float(*getFrictionT)(const Block_*);
    auto getFriction = (getFrictionT)dlsym("?getFriction@Block@@QEBAMXZ");
    if (getFriction != NULL) {
        *getFile("generated/block/data/friction.txt") << getFriction(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getFriction@Block@@QEBAMXZ" << std::endl;
    }
}
