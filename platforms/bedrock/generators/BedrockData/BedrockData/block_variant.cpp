#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_variant(const Block* block) {
    *getFile("generated/block/data/variant.txt") << block->getVariant() << std::endl;
}
