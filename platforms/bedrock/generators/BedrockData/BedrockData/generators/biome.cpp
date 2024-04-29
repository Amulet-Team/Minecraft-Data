#include "generators.hpp"
#include "logging.hpp"
#include <string>
#include "MC/Biome.hpp"
#include "MC/Minecraft.hpp"
#include "MC/Level.hpp"
#include <functional>
#include <iostream>


using namespace MinecraftAPI;


void saveBiome(Biome& biome) {
	if (std::string* name = biome.getName()) {
		logToFile("generated/biome/biomes.txt", *name);
	}
	else {
		logToFile("generated/biome/biomes.txt", "NULL");
	}
}


namespace Data {
	void biome() {
		debug("Running data generator: Block");
		Minecraft* minecraft = Minecraft::get();
		if (Level* level = minecraft->getLevel()) {
			if (BiomeRegistry const* biome_registry = level->getBiomeRegistry()) {
				biome_registry->forEachBiome(saveBiome);
				for (int i = 0; i < 512; i++) {
					if (Biome* biome = biome_registry->lookupById(i)) {
						if (std::string* name = biome->getName()) {
							logToFile("generated/biome/biome_id_map.txt", std::to_string(i) + ":" + *name);
						}
					}
				}
			}
		}
	}
};
