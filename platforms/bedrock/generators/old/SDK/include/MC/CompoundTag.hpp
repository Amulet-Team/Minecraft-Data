#pragma once
#include "../Global.h"
#include "Tag.hpp"
#include "BlockActor.hpp"

class CompoundTag : public Tag {
public:
	static std::unique_ptr<CompoundTag> create();
	static std::unique_ptr<CompoundTag> fromBlockActor(BlockActor* ble);
};
