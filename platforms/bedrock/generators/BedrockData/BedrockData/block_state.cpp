#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/IDataOutput.hpp>
#include <MC/CompoundTag.hpp>

#include <MC/NbtIo.hpp>
#include "minecraft.hpp"
#include "get_file.hpp"


std::string write_compound(const CompoundTag* tag) {
    void* vtbl = dlsym("??_7StringByteOutput@@6B@");
    string result = "";
    void* iDataOutput[2] = { vtbl, &result };
    NbtIo::write(tag, (IDataOutput&)iDataOutput);
    return result;
}


void block_state(const Block* block) {
    const CompoundTag* tag = &block->getSerializationId();
    std::string out = write_compound(tag);
    getFile("generated/block/data/states.bin", true)->write(out.c_str(), out.size());
}
