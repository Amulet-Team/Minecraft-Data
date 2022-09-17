#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include <MC/Biome.hpp>
#include <MC/BiomeRegistry.hpp>
#include <MC/Minecraft.hpp>
#include <MC/Level.hpp>
#include "get_file.hpp"

int Biome::getId() const {
	return dAccess<int, 120>(this);
}

std::string const& Biome::getName() const {
	return dAccess<std::string, 8>(this);
}


TInstanceHook(Biome&, "?registerBiome@BiomeRegistry@@QEAAAEAVBiome@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z", BiomeRegistry, const std::string& name) {
	Biome& biome = original(this, name);
	int biome_id = biome.getId();
	const std::string& biome_name = biome.getName();
	*getFile("generated/biome/biome_map.txt") << biome_id << "|" << biome_name << std::endl;
	return biome;
}
