#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_runtime_id(const Block_* block) {
    typedef unsigned int&(*getRuntimeIdT)(const Block_*);
    auto getRuntimeId = (getRuntimeIdT)dlsym("?getRuntimeId@Block@@QEBAAEBIXZ");
    if (getRuntimeId != NULL) {
        *getFile("generated/block/data/runtime_id.txt") << getRuntimeId(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getRuntimeId@Block@@QEBAAEBIXZ" << std::endl;
    }
}
