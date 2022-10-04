#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_interactive(const Block_* block) {
    typedef bool(*isInteractiveBlockT)(const Block_*);
    auto isInteractiveBlock = (isInteractiveBlockT)dlsym("?isInteractiveBlock@Block@@QEBA_NXZ");
    if (isInteractiveBlock != NULL) {
        *getFile("generated/block/data/interactive.txt") << isInteractiveBlock(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isInteractiveBlock@Block@@QEBA_NXZ" << std::endl;
    }
}
