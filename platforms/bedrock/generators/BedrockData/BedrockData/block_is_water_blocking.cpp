#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_water_blocking(const Block* block) {
    *getFile("generated/block/data/water_blocking.txt") << block->isWaterBlocking() << std::endl;
}
