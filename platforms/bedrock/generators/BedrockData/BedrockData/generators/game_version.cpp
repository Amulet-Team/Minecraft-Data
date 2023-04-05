#pragma once
#include "logging.hpp"
#include "generators.hpp"
#include "MC/GameVersion.hpp"

using namespace MinecraftAPI;


void Data::game_version() {
	logToFile("generated/version/build_version.txt", std::format("{}.{}.{}.{}", GameVersion::major(), GameVersion::minor(), GameVersion::patch(), GameVersion::revision()));
}
