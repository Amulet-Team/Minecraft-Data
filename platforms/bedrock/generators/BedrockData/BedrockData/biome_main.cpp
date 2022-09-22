#pragma once
#include "pch.h"

#include "minecraft.hpp"


void biome_map_validate();


void biome_main(Minecraft_*) {
	biome_map_validate();
}
