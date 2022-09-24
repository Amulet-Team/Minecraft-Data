#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_light_emission(const Block_* block) {
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
}
