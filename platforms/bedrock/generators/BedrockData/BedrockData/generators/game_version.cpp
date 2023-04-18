#pragma once
#include "logging.hpp"
#include "generators.hpp"
#include "MC/GameVersion.hpp"

using namespace MinecraftAPI;


void Data::game_version() {
	debug("Running data generator: Game Version");
	logToFile("generated/version/build_version.txt", std::format("{}.{}.{}.{}", GameVersion::major(), GameVersion::minor(), GameVersion::patch(), GameVersion::revision()));
}
