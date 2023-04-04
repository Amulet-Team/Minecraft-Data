#include "tests.hpp"
#include "get_file.hpp"
#include <thread>
#include <chrono>

#include "MC/DataVersion.hpp"
#include "MC/GameVersion.hpp"


using namespace MinecraftAPI;


void Test::test_DataVersion() {
	if (DataVersion::actorDigestFormat() == -1) {
		throw "test_DataVersion: Could not find actorDigestFormat";
	}
	if (DataVersion::blendVersion() == -1) {
		throw "test_DataVersion: Could not find blendVersion";
	}
	if (DataVersion::levelChunkFormat() == -1) {
		throw "test_DataVersion: Could not find levelChunkFormat";
	}
	if (DataVersion::storageVersion() == -1) {
		throw "test_DataVersion: Could not find storageVersion";
	}
	if (DataVersion::subChunkFormat() == -1) {
		throw "test_DataVersion: Could not find subChunkFormat";
	}
}
