#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_destroy_speed(const Block_* block) {
    typedef float(*getDestroySpeedT)(const Block_*);
    auto getDestroySpeed = (getDestroySpeedT)dlsym("?getDestroySpeed@Block@@QEBAMXZ");
    if (getDestroySpeed != NULL) {
        *getFile("generated/block/data/destroy_speed.txt") << getDestroySpeed(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getDestroySpeed@Block@@QEBAMXZ" << std::endl;
    }
}
