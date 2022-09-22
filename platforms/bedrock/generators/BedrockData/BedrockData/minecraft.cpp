#pragma once
#include "pch.h"

#include "get_file.hpp"
#include "minecraft.hpp"


std::string const& SemVersion_::asString() const {
	typedef const std::string& (*t_asStringOriginal)(const SemVersion_*);
	auto asStringOriginal = (t_asStringOriginal)dlsym("?asString@SemVersion@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	if (asStringOriginal == NULL) {
		*getFile("generated/err.txt") << "?asString@SemVersion@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ" << std::endl;
		return "null";
	}
	else {
		return asStringOriginal(this);
	}
}


void BlockPalette_::forEachBlock(blockCallbackT callback) {
	typedef Block_& (*getBlockT)(BlockPalette_*, unsigned int&);
	auto getBlock = (getBlockT)dlsym("?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z");
	if (getBlock != NULL) {
		// This may cause problems
		unsigned int palette_len = (*(unsigned int*)(this + 0x78) - *(unsigned int*)(this + 0x70)) / 8;
		// handle error state
		if (palette_len < 100000) {
			for (unsigned int block_id = 0; block_id < palette_len; block_id++) {
				Block_* block = &getBlock(this, block_id);
				callback(block);
			}
		}
		else {
			*getFile("generated/err.txt") << "issue with block pallete length" << std::endl;
		}
	}
	else {
		*getFile("generated/err.txt") << "?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z" << std::endl;
	}
}
