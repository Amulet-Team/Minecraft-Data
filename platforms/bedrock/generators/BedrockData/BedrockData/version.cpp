#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void currentActorDigestFormat() {
    enum ActorDigestFormat* v = (enum ActorDigestFormat*)dlsym("?CurrentActorDigestFormat@SharedConstants@@3W4ActorDigestFormat@@B");
    if (v != NULL) {
        *getFile("generated/version/actor_digest_version.txt") << *v;
    }
    else {
        *getFile("generated/err.txt") << "?CurrentActorDigestFormat@SharedConstants@@3W4ActorDigestFormat@@B" << std::endl;
    }
}


void currentBlendVersion() {
    enum BlendVersion* v = (enum BlendVersion*)dlsym("?CurrentBlendVersion@SharedConstants@@3W4BlendVersion@@B");
    if (v != NULL) {
        *getFile("generated/version/blend_version.txt") << *v;
    }
    else {
        *getFile("generated/err.txt") << "?CurrentBlendVersion@SharedConstants@@3W4BlendVersion@@B" << std::endl;
    }
}


void currentGameSemVersion() {
    SemVersion_* gameVersion = (SemVersion_*)dlsym("?CurrentGameSemVersion@SharedConstants@@3VSemVersion@@B");
    if (gameVersion != NULL) {
        *getFile("generated/version/game_version.txt") << gameVersion->asString();
    }
    else {
        *getFile("generated/err.txt") << "?CurrentGameSemVersion@SharedConstants@@3VSemVersion@@B" << std::endl;
    }
}


void currentLevelChunkFormat() {
    enum LevelChunkFormat* v = (enum LevelChunkFormat*)dlsym("?CurrentLevelChunkFormat@SharedConstants@@3W4LevelChunkFormat@@B");
    if (v != NULL) {
        *getFile("generated/version/level_chunk_format.txt") << *v;
    }
    else {
        *getFile("generated/err.txt") << "?CurrentLevelChunkFormat@SharedConstants@@3W4LevelChunkFormat@@B" << std::endl;
    }
}


void currentStorageVersion() {
    enum StorageVersion* v = (enum StorageVersion*)dlsym("?CurrentStorageVersion@SharedConstants@@3W4StorageVersion@@B");
    if (v != NULL) {
        *getFile("generated/version/storage_version.txt") << *v;
    }
    else {
        *getFile("generated/err.txt") << "?CurrentStorageVersion@SharedConstants@@3W4StorageVersion@@B" << std::endl;
    }
}


void currentSubChunkFormat() {
    enum SubChunkFormat* v = (enum SubChunkFormat*)dlsym("?CurrentSubChunkFormat@SharedConstants@@3W4SubChunkFormat@@B");
    if (v != NULL) {
        *getFile("generated/version/sub_chunk_format.txt") << *v;
    }
    else {
        *getFile("generated/err.txt") << "?CurrentSubChunkFormat@SharedConstants@@3W4SubChunkFormat@@B" << std::endl;
    }
}


std::array<int, 4> getBuildVersion() {
    std::array<int, 4> version = { -1, -1, -1, -1 };
    int* num;
    num = (int*)dlsym("?MajorVersion@SharedConstants@@3HB");
    if (num != NULL) {
        version[0] = *num;
    }
    else {
        *getFile("generated/err.txt") << "?MajorVersion@SharedConstants@@3HB" << std::endl;
    }
    num = (int*)dlsym("?MinorVersion@SharedConstants@@3HB");
    if (num != NULL) {
        version[1] = *num;
    }
    else {
        *getFile("generated/err.txt") << "?MinorVersion@SharedConstants@@3HB" << std::endl;
    }
    num = (int*)dlsym("?PatchVersion@SharedConstants@@3HB");
    if (num != NULL) {
        version[2] = *num;
    }
    else {
        *getFile("generated/err.txt") << "?PatchVersion@SharedConstants@@3HB" << std::endl;
    }
    num = (int*)dlsym("?RevisionVersion@SharedConstants@@3HB");
    if (num != NULL) {
        version[3] = *num;
    }
    else {
        *getFile("generated/err.txt") << "?RevisionVersion@SharedConstants@@3HB" << std::endl;
    }
    return version;
}


void buildVersion() {
    std::array<int, 4> version = getBuildVersion();
    *getFile("generated/version/build_version.txt") << version[0] << "." << version[1] << "." << version[2] << "." << version[3];
}


void version() {
    currentActorDigestFormat();
    currentBlendVersion();
    currentGameSemVersion();
    currentLevelChunkFormat();
    currentStorageVersion();
    currentSubChunkFormat();
    buildVersion();
}
