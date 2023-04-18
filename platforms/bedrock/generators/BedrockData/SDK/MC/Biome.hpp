#pragma once
#include <string>
#include "GameVersion.hpp"


namespace MinecraftAPI {
	class Biome {
	public:
		static void* vftable;

		std::string* getName() const {
			int thisVersion[4] = { GameVersion::major(), GameVersion::minor(), GameVersion::patch(), GameVersion::revision() };
			int v116[4] = { 1, 16, 210, 5 };
			int v11930[4] = { 1, 19, 30, 4 };

			if (compareVersions(thisVersion, v11930) & GreaterEqual ) {
				std::string* name = (std::string*)(this + 16);
				if (name->size()) {
					return name;
				}
			}
			else if (compareVersions(thisVersion, v116) & GreaterEqual) {
				std::string* name = (std::string*)(this + 8);
				if (name->size()) {
					return name;
				}
			}
			
			return nullptr;
		}
	};
}
