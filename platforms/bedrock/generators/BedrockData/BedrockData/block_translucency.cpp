#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_translucency(const Block_* block) {
    typedef float(*getTranslucencyT)(const Block_*);
    auto getTranslucency = (getTranslucencyT)dlsym("?getTranslucency@Block@@QEBAMXZ");
    if (getTranslucency != NULL) {
        *getFile("generated/block/data/translucency.txt") << getTranslucency(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getTranslucency@Block@@QEBAMXZ" << std::endl;
    }
}
