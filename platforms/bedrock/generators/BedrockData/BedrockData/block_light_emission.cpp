#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/Brightness.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"

void block_light_emission(const Block* block) {
    Brightness light = block->getLightEmission();
    const unsigned char* light_value = (unsigned char*)&light;
    const int light_value_int = *light_value;
    *getFile("generated/block/data/light_emission.txt") << light_value_int << std::endl;
}
