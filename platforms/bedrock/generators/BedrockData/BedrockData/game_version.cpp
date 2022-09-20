#include "pch.h"

#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#include <MC/SharedConstants.hpp>
#include <MC/SemVersion.hpp>

#include "get_file.hpp"


void currentActorDigestFormat() {
    std::ofstream& f = *getFile("generated/version/actor_digest_version.txt");
    enum ActorDigestFormat* v = (enum ActorDigestFormat*)dlsym("?CurrentActorDigestFormat@SharedConstants@@3W4ActorDigestFormat@@B");
    if (v != NULL) {
        f << *v;
    }
    else {
        f << "null";
    }
}


void currentBlendVersion() {
    std::ofstream& f = *getFile("generated/version/blend_version.txt");
    enum BlendVersion* v = (enum BlendVersion*)dlsym("?CurrentBlendVersion@SharedConstants@@3W4BlendVersion@@B");
    if (v != NULL) {
        f << *v;
    }
    else {
        f << "null";
    }
}


void currentGameSemVersion() {
    std::ofstream& f = *getFile("generated/version/game_version.txt");
    SemVersion* gameVersion = (SemVersion*)dlsym("?CurrentGameSemVersion@SharedConstants@@3VSemVersion@@B");
    if (gameVersion != NULL) {
        f << gameVersion->asString();
    }
    else {
        f << "null";
    }
}


void currentLevelChunkFormat() {
    std::ofstream& f = *getFile("generated/version/level_chunk_format.txt");
    enum LevelChunkFormat* v = (enum LevelChunkFormat*)dlsym("?CurrentLevelChunkFormat@SharedConstants@@3W4LevelChunkFormat@@B");
    if (v != NULL) {
        f << *v;
    }
    else {
        f << "null";
    }
}


void currentStorageVersion() {
    std::ofstream& f = *getFile("generated/version/storage_version.txt");
    enum StorageVersion* v = (enum StorageVersion*)dlsym("?CurrentStorageVersion@SharedConstants@@3W4StorageVersion@@B");
    if (v != NULL) {
        f << *v;
    }
    else {
        f << "null";
    }
}


void currentSubChunkFormat() {
    std::ofstream& f = *getFile("generated/version/sub_chunk_format.txt");
    enum SubChunkFormat* v = (enum SubChunkFormat*)dlsym("?CurrentSubChunkFormat@SharedConstants@@3W4SubChunkFormat@@B");
    if (v != NULL) {
        f << *v;
    }
    else {
        f << "null";
    }
}


void buildVersion() {
    std::ofstream& f = *getFile("generated/version/build_version.txt");
    int* num;
    num = (int*)dlsym("?MajorVersion@SharedConstants@@3HB");
    if (num != NULL) {
        f << *num << ".";
    }
    else {
        f << "null.";
    }
    num = (int*)dlsym("?MinorVersion@SharedConstants@@3HB");
    if (num != NULL) {
        f << *num << ".";
    }
    else {
        f << "null.";
    }
    num = (int*)dlsym("?PatchVersion@SharedConstants@@3HB");
    if (num != NULL) {
        f << *num << ".";
    }
    else {
        f << "null.";
    }
    num = (int*)dlsym("?RevisionVersion@SharedConstants@@3HB");
    if (num != NULL) {
        f << *num;
    }
    else {
        f << "null";
    }
}


void game_version_main() {
    currentActorDigestFormat();
    currentBlendVersion();
    currentGameSemVersion();
    currentLevelChunkFormat();
    currentStorageVersion();
    currentSubChunkFormat();
    buildVersion();
}
