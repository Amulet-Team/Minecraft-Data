#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_entity_type(const Block* block) {
    *getFile("generated/block/data/block_entity.txt") << block->getBlockEntityType() << std::endl;
}
