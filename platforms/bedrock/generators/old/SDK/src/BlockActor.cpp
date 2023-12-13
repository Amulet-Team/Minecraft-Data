#pragma once
#include "pch.h"
#include <MC/BlockActor.hpp>
#include <GetVirtual.hpp>

class CompoundTag;


VirtualRegex SaveFinder("?save@", "@@UEBA_NAEAVCompoundTag@@@Z", "BlockActor");
typedef bool (*saveT)(CompoundTag&);


bool BlockActor::callSave(CompoundTag& tag) const {
	auto save = (saveT)SaveFinder.get((void***)this);
	return save(tag);
};
