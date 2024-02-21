#include "Level.hpp"
#include "BlockPalette.hpp"

#include "HookAPI.h"
#include <iostream>
#include <string>

using namespace MinecraftAPI;


Level::_getDimensionT Level::_getDimension = (Level::_getDimensionT)dlsym("?getDimension@Level@@QEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z");


// 66/67 - getBiomeRegistry


BlockPalette* Level::getBlockPalette() {
	if (_getBlockPaletteT _getBlockPalette = findVirtual<_getBlockPaletteT, Level>(this, "?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ", 100)) {
		return &_getBlockPalette(this);
	}
	return nullptr;
};


BiomeRegistry const* Level::getBiomeRegistry() const {
	if (_getBiomeRegistryT _getBiomeRegistry = findVirtual<_getBiomeRegistryT, const Level>(this, "?getBiomeRegistry@Level@@UEBAAEBVBiomeRegistry@@XZ", 100)) {
		BiomeRegistry const& biome_registry = _getBiomeRegistry(this);
		if ((unsigned long long) & biome_registry > 0xFFFF) {
			return &biome_registry;
		}
	}
	return nullptr;
};
