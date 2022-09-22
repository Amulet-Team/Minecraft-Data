#pragma once
#include "pch.h"

#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#include <MC/Block.hpp>

#include "minecraft.hpp"
#include "get_file.hpp"


void block_entity_type(const Block_*);
void block_destroy_speed(const Block_*);
void block_friction(const Block_*);
void block_is_container(const Block_*);
void block_is_interactive(const Block_*);
void block_is_motion_blocking(const Block_*);
void block_is_solid(const Block_*);
void block_is_unbreakable(const Block_*);
void block_is_water_blocking(const Block_*);
void block_light(const Block*);
void block_light_emission(const Block*);
void block_map_colour(const Block*);
void block_may_pick(const Block_*);
void block_min_game_version(const Block*);
void block_name(const Block*);
void block_runtime_id(const Block_*);
void block_state(const Block*);
void block_translucency(const Block_*);
void block_variant(const Block_*);


void forEachBlock(Block_* block_) {
    Block* block = (Block*)block_;
    block_entity_type(block_);
    block_destroy_speed(block_);
    block_friction(block_);
    block_is_container(block_);
    block_is_interactive(block_);
    block_is_motion_blocking(block_);
    block_is_solid(block_);
    block_is_unbreakable(block_);
    block_is_water_blocking(block_);
    block_light(block);
    block_light_emission(block);
    block_map_colour(block);
    block_may_pick(block_);
    block_min_game_version(block);
    block_name(block);
    block_runtime_id(block_);
    block_state(block);
    block_translucency(block_);
    block_variant(block_);
}


void block_data(Minecraft_* minecraft) {
    typedef Level_* (*t_getLevel)(const Minecraft_*);
    auto getLevel = (t_getLevel)dlsym("?getLevel@Minecraft@@QEBAPEAVLevel@@XZ");
    if (getLevel != NULL) {
        Level_* level = getLevel(minecraft);

        typedef BlockPalette_& const (*t_getBlockPalette)(const Level_*);
        auto getBlockPalette = (t_getBlockPalette)dlsym("?getBlockPalette@Level@@UEBAAEBVBlockPalette@@XZ");
        if (getBlockPalette != NULL) {
            getBlockPalette(level).forEachBlock(forEachBlock);
        }
        else {
            *getFile("generated/err.txt") << "getBlockPalette@Level" << std::endl;
        }
    }
    else {
        *getFile("generated/err.txt") << "getLevel@Minecraft" << std::endl;
    }
}
