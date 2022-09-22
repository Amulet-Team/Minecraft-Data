#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_container(const Block* block) {
    *getFile("generated/block/data/is_container.txt") << block->isContainerBlock() << std::endl;
}
