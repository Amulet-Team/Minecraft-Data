#pragma once
#include "pch.h"

#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


void block_entity_type(const Block_* block) {
    typedef enum BlockActorType (*getBlockEntityTypeT)(const Block_*);
    auto getBlockEntityType = (getBlockEntityTypeT)dlsym("?getBlockEntityType@Block@@QEBA?AW4BlockActorType@@XZ");
    if (getBlockEntityType != NULL) {
        *getFile("generated/block/data/block_entity.txt") << getBlockEntityType(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getBlockEntityType@Block@@QEBA?AW4BlockActorType@@XZ" << std::endl;
    }
}
