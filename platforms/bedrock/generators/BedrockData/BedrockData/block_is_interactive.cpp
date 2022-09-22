#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_interactive(const Block* block) {
    *getFile("generated/block/data/interactive.txt") << block->isInteractiveBlock() << std::endl;
}
