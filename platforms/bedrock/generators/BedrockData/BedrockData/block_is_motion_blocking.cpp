#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_motion_blocking(const Block_* block) {
    typedef bool(*isMotionBlockingBlockT)(const Block_*);
    auto isMotionBlockingBlock = (isMotionBlockingBlockT)dlsym("?isMotionBlockingBlock@Block@@QEBA_NXZ");
    if (isMotionBlockingBlock != NULL) {
        *getFile("generated/block/data/motion_blocking.txt") << isMotionBlockingBlock(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isMotionBlockingBlock@Block@@QEBA_NXZ" << std::endl;
    }
}
