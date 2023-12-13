#pragma once
#include <MC/nbt/CompoundTag.hpp>


namespace MinecraftAPI {
	class BlockActor {
		typedef bool (*_saveT)(const BlockActor*, CompoundTag const&);

	public:
		bool save(CompoundTag const&) const;
	};
}
