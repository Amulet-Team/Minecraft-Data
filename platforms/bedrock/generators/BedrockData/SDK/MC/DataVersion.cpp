#include "DataVersion.hpp"
#include "HookAPI.h"

using namespace MinecraftAPI;

// Added 1.19.1.01
enum ActorDigestFormat* DataVersion::_ActorDigestFormat = (enum ActorDigestFormat*)dlsym("?CurrentActorDigestFormat@SharedConstants@@3W4ActorDigestFormat@@B");
// Added 1.18.30.04
enum BlendVersion* DataVersion::_BlendVersion = (enum BlendVersion*)dlsym("?CurrentBlendVersion@SharedConstants@@3W4BlendVersion@@B");
// Added 1.9.0.15
enum LevelChunkFormat* DataVersion::_LevelChunkFormat = (enum LevelChunkFormat*)dlsym("?CurrentLevelChunkFormat@SharedConstants@@3W4LevelChunkFormat@@B");
// Added 1.9.0.15
enum StorageVersion* DataVersion::_StorageVersion = (enum StorageVersion*)dlsym("?CurrentStorageVersion@SharedConstants@@3W4StorageVersion@@B");
// Added 1.9.0.15
enum SubChunkFormat* DataVersion::_SubChunkFormat = (enum SubChunkFormat*)dlsym("?CurrentSubChunkFormat@SharedConstants@@3W4SubChunkFormat@@B");
