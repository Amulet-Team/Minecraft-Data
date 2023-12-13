#pragma once
#include "pch.h"

#include <MC/NbtIo.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/BlockActor.hpp>


std::unique_ptr<CompoundTag> CompoundTag::create() {
    return std::unique_ptr<CompoundTag>((CompoundTag*)Tag::newTag(Tag::Type::Compound).release());
}


//std::unique_ptr<CompoundTag> CompoundTag::fromBlockActor(BlockActor* blockActor) {
//    auto tag = CompoundTag::create();
//    blockActor->save(*tag);
//    return std::move(tag);
//}
