#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_variant(const Block_* block) {
    typedef int(*getVariantT)(const Block_*);
    auto getVariant = (getVariantT)dlsym("?getVariant@Block@@QEBAHXZ");
    if (getVariant != NULL) {
        *getFile("generated/block/data/variant.txt") << getVariant(block) << std::endl;
    }
    else {
        *getFile("generated/err.txt") << "?getVariant@Block@@QEBAHXZ" << std::endl;
    }
}
