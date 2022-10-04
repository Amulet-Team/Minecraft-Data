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
	// ?getMapColor@BlockLegacy@@MEBA?AVColor@mce@@XZ
	virtual mce::Color getMapColor() const;
	// ?getBlockEntityType@BlockLegacy@@QEBA?AW4BlockActorType@@XZ
	MCAPI BlockActorType getBlockEntityType() const;
	// ?getRequiredBaseGameVersion@BlockLegacy@@QEBAAEBVBaseGameVersion@@XZ
	MCAPI BaseGameVersion const& getRequiredBaseGameVersion() const;
};
