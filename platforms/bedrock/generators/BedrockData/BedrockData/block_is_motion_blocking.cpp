#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_motion_blocking(const Block* block) {
    *getFile("generated/block/data/motion_blocking.txt") << block->isMotionBlockingBlock() << std::endl;
}
