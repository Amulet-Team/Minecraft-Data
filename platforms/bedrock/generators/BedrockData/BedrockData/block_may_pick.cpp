#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_may_pick(const Block* block) {
    *getFile("generated/block/data/may_pick.txt") << block->mayPick() << std::endl;
}
