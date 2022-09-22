#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_solid(const Block* block) {
    *getFile("generated/block/data/solid.txt") << block->isSolid() << std::endl;
}
