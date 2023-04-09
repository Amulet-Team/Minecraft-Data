#pragma once

#include "BlockPalette.hpp"



namespace MinecraftAPI {
	class Level {
		// ?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ
		typedef BlockPalette& (*_getBlockPaletteT)(Level*);
		// ?getBlockPalette@Level@@UEBAAEBVBlockPalette@@XZ
		//typedef BlockPalette const& _getBlockPaletteT(const Level*);

	public:
		BlockPalette* getBlockPalette();
		//BlockPalette const& getBlockPalette() const;
	};
}
