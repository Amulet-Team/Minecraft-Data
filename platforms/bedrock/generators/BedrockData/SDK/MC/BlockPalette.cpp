#include "BlockPalette.hpp"
#include "HookAPI.h"
#include "logging.hpp"


using namespace MinecraftAPI;

// Added 1.9.0.15
BlockPalette::_getBlockT BlockPalette::_getBlock = (BlockPalette::_getBlockT)dlsym("?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z");

unsigned int BlockPalette::len() {
	// The array pointer moves around so find it dynamically
	for (uintptr_t off = 0; off < 100; off++) {
		void**** block_arr_start_ptr = (void****)this + off;
		if (isBadReadPtr(block_arr_start_ptr)) {
			continue;
		}
		void*** block_arr = *block_arr_start_ptr;
		if (isBadReadPtr(block_arr)) {
			continue;
		}
		void** block = *block_arr;
		if (isBadReadPtr(block)) {
			continue;
		}
		void* vtable = *block;
		if (vtable != Block::vftable) {
			continue;
		}

		void**** block_arr_end_ptr = (void****)this + off + 1;
		if (isBadReadPtr(block_arr_end_ptr)) {
			continue;
		}
		unsigned int palette_len = (unsigned int)(*block_arr_end_ptr - *block_arr_start_ptr);
		if (palette_len > 100000) {
			debug("Palette len too large. Probably an offset error.");
			return 0;
		}
		return palette_len;
	}
	debug("Could not find palette");
	return 0;
}
