#pragma once
#include "util/get_file.hpp"
#include "generators.hpp"
#include "MC/GameVersion.hpp"

using namespace MinecraftAPI;


void Data::game_version() {
	*getFile("generated/version/build_version.txt") << GameVersion::major() << "." << GameVersion::minor() << "." << GameVersion::patch() << "." << GameVersion::revision();
}
