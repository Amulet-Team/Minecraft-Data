#pragma once
#include "logging.hpp"
#include "generators.hpp"
#include "MC/DataVersion.hpp"

using namespace MinecraftAPI;


void Data::data_version() {
	logToFile("generated/version/actor_digest_version.txt", DataVersion::actorDigestFormat());
	logToFile("generated/version/blend_version.txt", DataVersion::blendVersion());
	logToFile("generated/version/level_chunk_format.txt", DataVersion::levelChunkFormat());
	logToFile("generated/version/storage_version.txt", DataVersion::storageVersion());
	logToFile("generated/version/sub_chunk_format.txt", DataVersion::subChunkFormat());
}
