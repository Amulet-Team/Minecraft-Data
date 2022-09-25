#pragma once
#include "pch.h"
#include <string>

class Minecraft_ {};
class Level_ {};

class SemVersion_{
public:
	std::string const& asString() const;
};

class HashedString_ {
public:
	std::string const & getString() const;
	//class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> > const& __cdecl getString(void)const;
};

class BiomeRegistry_ {};
class Biome_ {};

class CompoundTag_ {};
class IDataOutput_ {};
class BlockLegacy_ {};
class Block_ {
public:
	BlockLegacy_ const* getLegacyBlock() const;
};


typedef void (*blockCallbackT)(const Block_*);
class BlockPalette_ {
public:
	void forEachBlock(blockCallbackT) const;
};

struct Brightness_ {
	char a[0x800];
public:
	Brightness_();
	char getValue();
};

class Colour_ {
public:
	float r;
	float g;
	float b;
	float a;
};
