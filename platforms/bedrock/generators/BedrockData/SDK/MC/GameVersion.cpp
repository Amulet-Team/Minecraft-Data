#include "GameVersion.hpp"
#include "HookAPI.h"

using namespace MinecraftAPI;

// Added 1.9.0.15
int* GameVersion::_major = (int*)dlsym("?MajorVersion@SharedConstants@@3HB");
// Added 1.9.0.15
int* GameVersion::_minor = (int*)dlsym("?MinorVersion@SharedConstants@@3HB");
// Added 1.9.0.15
int* GameVersion::_patch = (int*)dlsym("?PatchVersion@SharedConstants@@3HB");
// Added 1.9.0.15
int* GameVersion::_revision = (int*)dlsym("?RevisionVersion@SharedConstants@@3HB");


VersionComparison compareVersions(int v1[4], int v2[4]) {
    for (int i = 0; i < 4; i++) {
        if (v1[i] > v2[i]) {
            return Greater;
        } else if (v1[i] < v2[i]) {
            return Less;
        }
    }
    return Equal;
}
