#include "Level.hpp"
#include "BlockPalette.hpp"

#include "HookAPI.h"
#include <iostream>

using namespace MinecraftAPI;


// 66/67 - getBiomeRegistry


BlockPalette* Level::getBlockPalette() {
	_getBlockPaletteT _getBlockPalette = getVirtual<_getBlockPaletteT, Level>(this, 68, "?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ");
	if (_getBlockPalette != nullptr) {
		return &_getBlockPalette(this);
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
