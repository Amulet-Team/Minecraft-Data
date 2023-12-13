#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/IDataOutput.hpp>
#include <MC/CompoundTag.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"
#include "nbt.hpp"


void block_state(const Block* block) {
    const CompoundTag* tag = &block->getSerializationId();
    std::string out = write_compound(tag);
    getFile("generated/block/data/states.bin", true)->write(out.c_str(), out.size());
}
