#pragma once
#include "pch.h"
#include <string>
#include <HookAPI.h>
#include <MC/NbtIo.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/BlockActor.hpp>
#include <MC/IDataOutput.hpp>


//std::unique_ptr<CompoundTag> CompoundTag::create() {
//    return std::unique_ptr<CompoundTag>((CompoundTag*)Tag::newTag(Tag::Type::Compound).release());
//}
//
//
//std::unique_ptr<CompoundTag> CompoundTag::fromBlockActor(BlockActor* blockActor) {
//    auto tag = CompoundTag::create();
//    blockActor->save(*tag);
//    return std::move(tag);
//}


std::string write_compound(const CompoundTag* tag) {
    void* vtbl = dlsym("??_7StringByteOutput@@6B@");
    std::string result = "";
    void* iDataOutput[2] = { vtbl, &result };
    NbtIo::write(tag, (IDataOutput&)iDataOutput);
    return result;
}
