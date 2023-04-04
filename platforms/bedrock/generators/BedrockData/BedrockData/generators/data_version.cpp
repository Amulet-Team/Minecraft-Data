#pragma once
#include "util/get_file.hpp"
#include "generators.hpp"
#include "MC/DataVersion.hpp"

using namespace MinecraftAPI;


void Data::data_version() {
	*getFile("generated/version/actor_digest_version.txt") << DataVersion::actorDigestFormat();
	*getFile("generated/version/blend_version.txt") << DataVersion::blendVersion();
	*getFile("generated/version/level_chunk_format.txt") << DataVersion::levelChunkFormat();
	*getFile("generated/version/storage_version.txt") << DataVersion::storageVersion();
	*getFile("generated/version/sub_chunk_format.txt") << DataVersion::subChunkFormat();
}
