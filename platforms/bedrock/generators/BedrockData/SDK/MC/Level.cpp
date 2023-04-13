#include "Level.hpp"
#include "BlockPalette.hpp"

#include "HookAPI.h"
#include <iostream>

using namespace MinecraftAPI;


// 66/67 - getBiomeRegistry


BlockPalette* Level::getBlockPalette() {
	for (int off = 0; off < 100; off++) {
		if (_getBlockPaletteT _getBlockPalette = getVirtual<_getBlockPaletteT, Level>(this, off, "?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ")) {
			return &_getBlockPalette(this);
		}
	}
	return nullptr;

	/*for (uintptr_t i = 0; i < 100; i++) {
		debug(i);
		std::vector<std::string> symbols = dlsym_reverse(*(* (uintptr_t**)this + i));
		if (symbols.size() < 50) {
			for (std::string symbol : symbols) {
				debug(symbol);
			}
		}
	}*/
};
