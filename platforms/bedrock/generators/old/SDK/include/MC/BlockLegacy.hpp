#pragma once
#include "../Global.h"
#include "BlockActor.hpp"
#include "Color.hpp"
#include "BaseGameVersion.hpp"

class Block;
class BlockSource;
class ItemStack;

class BlockLegacy {
public:
	mce::Color callGetMapColor() const;
	// ?getBlockEntityType@BlockLegacy@@QEBA?AW4BlockActorType@@XZ
	MCAPI BlockActorType getBlockEntityType() const;
	// ?getRequiredBaseGameVersion@BlockLegacy@@QEBAAEBVBaseGameVersion@@XZ
	MCAPI BaseGameVersion const& getRequiredBaseGameVersion() const;
};
