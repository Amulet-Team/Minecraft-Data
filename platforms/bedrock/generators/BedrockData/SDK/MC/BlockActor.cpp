#include <stdexcept>
#include "BlockActor.hpp"
#include "HookAPI.h"


using namespace MinecraftAPI;


bool BlockActor::save(CompoundTag const& tag) const {
	if (_saveT _save = findVirtual<_saveT, const BlockActor>(this, "?save@BlockActor@@UEBA_NAEAVCompoundTag@@@Z", 100)) {
		bool out = _save(this, tag);
		return out;
	}
	throw std::runtime_error("Could not find virtual function BlockActor::save");
};
