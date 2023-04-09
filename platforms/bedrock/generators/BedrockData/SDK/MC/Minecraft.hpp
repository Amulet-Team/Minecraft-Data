#pragma once

#include "Level.hpp"


namespace MinecraftAPI {
	class Minecraft {
		static Minecraft** Ptr;

		typedef Level* (*_getLevelT)(const Minecraft*);
		static _getLevelT _getLevel;

	public:
		static Minecraft* get();

		Level* getLevel() {
			if (_getLevel != nullptr) {
				return _getLevel(this);
			}
			return nullptr;
		}
	};
}
