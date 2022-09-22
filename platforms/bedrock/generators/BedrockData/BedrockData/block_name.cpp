#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/HashedString.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_name(const Block* block) {
    *getFile("generated/block/data/name.txt") << block->getName().getString() << std::endl;
}
