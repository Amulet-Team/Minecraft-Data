#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/BlockLegacy.hpp>
#include <MC/BaseGameVersion.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_min_game_version(const Block* block) {
    *getFile("generated/block/data/min_game_version.txt") << block->getLegacyBlock().getRequiredBaseGameVersion().asSemVersion().asString() << std::endl;
}
