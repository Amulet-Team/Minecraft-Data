#pragma once
#include "pch.h"

#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#include <MC/Block.hpp>
#include <MC/Brightness.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_light(const Block& block) {
    Brightness light = block.getLight();
    const unsigned char* light_value = (unsigned char*)&light;
    const int light_value_int = *light_value;
    *getFile("generated/block/data/light.txt") << light_value_int << std::endl;
}

void block_light_emission(const Block& block) {
    Brightness light = block.getLightEmission();
    const unsigned char* light_value = (unsigned char*)&light;
    const int light_value_int = *light_value;
    *getFile("generated/block/data/light_emission.txt") << light_value_int << std::endl;
}
