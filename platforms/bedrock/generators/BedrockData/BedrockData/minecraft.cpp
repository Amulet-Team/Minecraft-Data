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


void BlockPalette_::forEachBlock(blockCallbackT callback) const {
	typedef const Block_& (*getBlockT)(const BlockPalette_*, unsigned int&);
	auto getBlock = (getBlockT)dlsym("?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z");
	if (getBlock != NULL) {
		// This may cause problems
		unsigned int palette_len = (*(unsigned int*)(this + 0x78) - *(unsigned int*)(this + 0x70)) / 8;
		// handle error state
		if (palette_len < 100000) {
			for (unsigned int block_id = 0; block_id < palette_len; block_id++) {
				const Block_* block = &getBlock(this, block_id);
				callback(block);
			}
		}
		else {
			*getFile("generated/err.txt") << "issue with block pallete length " << palette_len << std::endl;
		}
	}
	else {
		*getFile("generated/err.txt") << "?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z" << std::endl;
	}
}


BlockLegacy_ const* Block_::getLegacyBlock() const {
	typedef BlockLegacy_ const&(*getLegacyBlockT)(const Block_*);
	auto getLegacyBlock_ = (getLegacyBlockT)dlsym("?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ");
	if (getLegacyBlock_ != NULL) {
		return &getLegacyBlock_(this);
	}
	else {
		return NULL;
	}
};


Brightness_::Brightness_(){
	memset(&a[0], 0xFF, sizeof(a));
}

char Brightness_::getValue() {
	return dAccess<unsigned char, 0>(this);
}


std::string const & HashedString_::getString() const {
//class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> > const& __cdecl HashedString_::getString(void)const {
	typedef std::string const &(*getStringT)(const HashedString_*);
	auto getString = (getStringT)dlsym("?getString@HashedString@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	if (getString != NULL) {
		return getString(this);
	}
	else {
		*getFile("generated/err.txt") << "?getString@HashedString@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ" << std::endl;
		return "null";
	}
}
