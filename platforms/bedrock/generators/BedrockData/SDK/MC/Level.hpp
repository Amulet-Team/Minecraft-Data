#pragma once

#include "BlockPalette.hpp"
#include "BiomeRegistry.hpp"


namespace MinecraftAPI {
	class Level {
		// ?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ
		typedef BlockPalette& (*_getBlockPaletteT)(Level*);
		// ?getBlockPalette@Level@@UEBAAEBVBlockPalette@@XZ
		//typedef BlockPalette const& _getBlockPaletteT(const Level*);

		typedef BiomeRegistry const& (*_getBiomeRegistryT)(const Level*);

	public:
		BlockPalette* getBlockPalette();
		const BiomeRegistry* getBiomeRegistry() const;
	};
}
