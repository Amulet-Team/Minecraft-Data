#include "generators.hpp"
#include "logging.hpp"
#include <string>
#include "MC/Biome.hpp"
#include "MC/Minecraft.hpp"
#include "MC/Level.hpp"
#include <functional>


using namespace MinecraftAPI;


void saveBiome(Biome& biome) {
	debug("biome");
	debug(std::to_string((unsigned long long) & biome));
	if (std::string* name = biome.getName()) {
		logToFile("generated/biome/biome_map.txt", *name);
	}
	else {
		logToFile("generated/biome/biome_map.txt", "NULL");
	}
}


namespace Data {
	void biome() {
		Minecraft* minecraft = Minecraft::get();
		if (Level* level = minecraft->getLevel()) {
			if (BiomeRegistry const* biome_registry = level->getBiomeRegistry()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10000));
				biome_registry->forEachBiome(saveBiome);
			}
		}
	}
};
