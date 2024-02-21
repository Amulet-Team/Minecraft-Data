#pragma once
#include "pch.h"

#include "minecraft.hpp"


void block_data(Minecraft_*);
void block_actor(Minecraft_*);
void block_alias();
void block_version();


void block(Minecraft_* minecraft) {
    //block_data(minecraft);
    //block_actor(minecraft);
    block_alias();
    block_version();
}
