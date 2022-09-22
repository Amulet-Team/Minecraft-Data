#pragma once
#include "pch.h"
#include <string>

class Minecraft_ {};
class Level_ {};

class SemVersion_{
public:
	std::string const& asString() const;
};

class BiomeRegistry_ {};
class Biome_ {};

class CompoundTag_ {};
class IDataOutput_ {};
class Block_ {};
class BlockLegacy_ {};

typedef void (*blockCallbackT)(Block_*);
class BlockPalette_ {
public:
	void forEachBlock(blockCallbackT);
};

class Brightness_ {};
