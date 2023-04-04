#include "DataVersion.hpp"
#include "HookAPI.h"

using namespace MinecraftAPI;

enum ActorDigestFormat* DataVersion::_ActorDigestFormat = (enum ActorDigestFormat*)dlsym("?CurrentActorDigestFormat@SharedConstants@@3W4ActorDigestFormat@@B");
enum BlendVersion* DataVersion::_BlendVersion = (enum BlendVersion*)dlsym("?CurrentBlendVersion@SharedConstants@@3W4BlendVersion@@B");
enum LevelChunkFormat* DataVersion::_LevelChunkFormat = (enum LevelChunkFormat*)dlsym("?CurrentLevelChunkFormat@SharedConstants@@3W4LevelChunkFormat@@B");
enum StorageVersion* DataVersion::_StorageVersion = (enum StorageVersion*)dlsym("?CurrentStorageVersion@SharedConstants@@3W4StorageVersion@@B");
enum SubChunkFormat* DataVersion::_SubChunkFormat = (enum SubChunkFormat*)dlsym("?CurrentSubChunkFormat@SharedConstants@@3W4SubChunkFormat@@B");
