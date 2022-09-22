#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_is_container(const Block_* block) {
    typedef bool(*isContainerBlockT)(const Block_*);
    auto isContainerBlock = (isContainerBlockT)dlsym("?isContainerBlock@Block@@QEBA_NXZ");
    if (isContainerBlock != NULL) {
        *getFile("generated/block/data/is_container.txt") << isContainerBlock(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?isContainerBlock@Block@@QEBA_NXZ" << std::endl;
    }
}
