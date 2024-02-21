#pragma once
#include "../Global.h"

class Block;
class Container;
class CompoundTag;
class BlockSource;
enum BlockActorType;

class BlockActor {
public:
	bool callSave(CompoundTag&) const;
};
