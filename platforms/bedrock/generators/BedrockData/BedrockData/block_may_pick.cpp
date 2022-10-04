#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_may_pick(const Block_* block) {
    typedef bool (*mayPickT)(const Block_*);
    auto mayPick = (mayPickT)dlsym("?mayPick@Block@@QEBA_NXZ");
    if (mayPick != NULL) {
        *getFile("generated/block/data/may_pick.txt") << mayPick(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?mayPick@Block@@QEBA_NXZ" << std::endl;
    }
}
