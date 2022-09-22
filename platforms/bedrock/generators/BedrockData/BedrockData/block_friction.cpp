#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_friction(const Block* block) {
    *getFile("generated/block/data/friction.txt") << block->getFriction() << std::endl;
}
