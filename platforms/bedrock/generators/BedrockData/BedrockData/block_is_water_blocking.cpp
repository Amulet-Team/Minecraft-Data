#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_water_blocking(const Block_* block) {
    typedef bool(*isWaterBlockingT)(const Block_*);
    auto isWaterBlocking = (isWaterBlockingT)dlsym("?isWaterBlocking@Block@@QEBA_NXZ");
    if (isWaterBlocking != NULL) {
        *getFile("generated/block/data/water_blocking.txt") << isWaterBlocking(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isWaterBlocking@Block@@QEBA_NXZ" << std::endl;
    }
}
