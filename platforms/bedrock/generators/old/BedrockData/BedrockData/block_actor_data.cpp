#pragma once
#include "pch.h"

#include <MC/Block.hpp>
#include <MC/BlockActor.hpp>
#include <MC/BlockActorFactory.hpp>
#include <MC/BlockPos.hpp>
#include <MC/BlockLegacy.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"
#include "nbt.hpp"


void block_actor_data(const Block* block) {
    auto blockActorType = block->getLegacyBlock().getBlockEntityType();
    if (blockActorType == 0) {
        getFile("generated/block/data/block_actor_data.bin", true)->write("\x01\x00\x00\x00", 4);
    }
    else {
        /*std::shared_ptr<BlockActor> blockActor = BlockActorFactory::createBlockEntity(blockActorType, BlockPos(), block->getLegacyBlock());
        auto compound = CompoundTag::fromBlockActor(blockActor.get());
        std::string out = write_compound(compound.get());
        getFile("generated/block/data/block_actor_data.bin", true)->write(out.c_str(), out.size());*/
    }
}
