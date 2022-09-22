#pragma once
#include "pch.h"

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_runtime_id(const Block* block) {
    *getFile("generated/block/data/runtime_id.txt") << block->getRuntimeId() << std::endl;
}
