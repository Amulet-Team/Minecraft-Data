#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/Brightness.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_light(const Block* block) {
    Brightness brightness = block->getLight();
    int light = *(unsigned char*)&brightness;
    *getFile("generated/block/data/light.txt") << light << std::endl;

    /*
    typedef Brightness_(*getLightT)(const Block_*);
    auto getLight = (getLightT)dlsym("?getLight@Block@@QEBA?AUBrightness@@XZ");
    if (getLight != NULL) {
        Brightness_ light = getLight(block);
        const int light_value_int = light.getValue();
        *getFile("generated/block/data/light.txt") << light_value_int << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getLight@Block@@QEBA?AUBrightness@@XZ" << std::endl;
    }
    */
}
