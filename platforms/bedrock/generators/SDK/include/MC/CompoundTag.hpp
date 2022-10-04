#pragma once
#include "../Global.h"
#include "Tag.hpp"
#include "BlockActor.hpp"

class CompoundTag : public Tag {
public:
	LIAPI static std::unique_ptr<CompoundTag> create();
	LIAPI static std::unique_ptr<CompoundTag> fromBlockActor(BlockActor* ble);
};
