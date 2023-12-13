#pragma once
#include <memory>


namespace MinecraftAPI {
	class CompoundTag {
	public:
		static std::unique_ptr<CompoundTag> create();
	};
}
