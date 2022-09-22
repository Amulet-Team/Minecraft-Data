#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_unbreakable(const Block* block) {
    *getFile("generated/block/data/unbreakable.txt") << block->isUnbreakable() << std::endl;
}
