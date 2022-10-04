#pragma once
#include "../Global.h"

class Block;
class Container;
class CompoundTag;
class BlockSource;
enum BlockActorType;

class BlockActor {
public:
	// ?save@BlockActor@@UEBA_NAEAVCompoundTag@@@Z
	virtual bool save(class CompoundTag&) const;
};
