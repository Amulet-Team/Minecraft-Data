#pragma once
#include "pch.h"

#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#include <MC/Block.hpp>
#include <MC/BlockLegacy.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_map_colour(const Block* block) {
    auto colour = block->getLegacyBlock().getMapColor();
    *getFile("generated/block/data/map_colour.txt") << colour.r << "," << colour.g << "," << colour.b << "," << colour.a << std::endl;
}
