#pragma once
#include <memory>
#include "../Global.h"
#include "BlockActor.hpp"
#include "BlockPos.hpp"
#include "BlockLegacy.hpp"

class BlockActorFactory {
public:
	// ?createBlockEntity@BlockActorFactory@@SA?AV?$shared_ptr@VBlockActor@@@std@@W4BlockActorType@@AEBVBlockPos@@AEBVBlockLegacy@@@Z
	MCAPI static std::shared_ptr<class BlockActor> createBlockEntity(BlockActorType, BlockPos const&, BlockLegacy const&);
};
