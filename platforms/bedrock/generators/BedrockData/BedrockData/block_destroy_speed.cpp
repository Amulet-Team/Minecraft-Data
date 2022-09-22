#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_destroy_speed(const Block* block) {
    *getFile("generated/block/data/destroy_speed.txt") << block->getDestroySpeed() << std::endl;
}
