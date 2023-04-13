#include "BlockPalette.hpp"
#include "HookAPI.h"
#include "logging.hpp"


using namespace MinecraftAPI;

// Added 1.9.0.15
BlockPalette::_getBlockT BlockPalette::_getBlock = (BlockPalette::_getBlockT)dlsym("?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z");

unsigned int BlockPalette::len() {
	// The array pointer moves around so find it dynamically
	for (uintptr_t off = 0; off < 100; off++) {
		debug("this");
		debug(std::to_string((uintptr_t)this));
		void**** block_arr_start_ptr = (void****)this + off;
		debug(std::to_string((uintptr_t)block_arr_start_ptr));
		if (isBadReadPtr(block_arr_start_ptr)) {
			continue;
		}
		void*** block_arr = *block_arr_start_ptr;
		debug(std::to_string((uintptr_t)block_arr));
		if (isBadReadPtr(block_arr)) {
			continue;
		}
		void** block = *block_arr;
		debug(std::to_string((uintptr_t)block));
		if (isBadReadPtr(block)) {
			continue;
		}
		void* vtable = *block;
		debug(std::to_string((uintptr_t)vtable));
		if (vtable != Block::vftable) {
			continue;
		}

		debug(std::to_string((uintptr_t)this));
		void**** block_arr_end_ptr = (void****)this + off + 1;
		if (isBadReadPtr(block_arr_end_ptr)) {
			continue;
		}
		debug(std::to_string(off));
		debug(std::to_string((uintptr_t)block_arr_start_ptr));
		debug(std::to_string((uintptr_t)block_arr_end_ptr));
		unsigned int palette_len = (unsigned int)(*block_arr_end_ptr - *block_arr_start_ptr);
		debug(std::to_string(palette_len));
		if (palette_len > 100000) {
			throw "Palette len too large. Probably an offset error.";
		}
		return palette_len;
	}
	throw "Could not find palette array.";
}
