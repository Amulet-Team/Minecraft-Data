#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_translucency(const Block* block) {
    *getFile("generated/block/data/translucency.txt") << block->getTranslucency() << std::endl;
}
