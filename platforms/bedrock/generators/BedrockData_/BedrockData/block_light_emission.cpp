#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/Brightness.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_light_emission(const Block* block) {
    Brightness brightness = block->getLightEmission();
    int emission = *(unsigned char*)&brightness;
    *getFile("generated/block/data/light_emission.txt") << emission << std::endl;

    /*
    typedef Brightness_(*getLightEmissionT)(const Block_*);
    auto getLightEmission = (getLightEmissionT)dlsym("?getLightEmission@Block@@QEBA?AUBrightness@@XZ");
    if (getLightEmission != NULL) {
        Brightness_ light = getLightEmission(block);
        const int light_value_int = light.getValue();
        *getFile("generated/block/data/light_emission.txt") << light_value_int << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getLightEmission@Block@@QEBA?AUBrightness@@XZ" << std::endl;
    }
    */
}
