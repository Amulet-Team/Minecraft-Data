#include "tests.hpp"
#include <thread>
#include <chrono>

#include "MC/GameVersion.hpp"


using namespace MinecraftAPI;


void Test::test_GameVersion() {
	if (GameVersion::major() == -1) {
		throw "test_GameVersion: Could not find major version";
	}
	if (GameVersion::minor() == -1) {
		throw "test_GameVersion: Could not find minor version";
	}
	if (GameVersion::patch() == -1) {
		throw "test_GameVersion: Could not find patch version";
	}
	if (GameVersion::revision() == -1) {
		throw "test_GameVersion: Could not find revision version";
	}
}
