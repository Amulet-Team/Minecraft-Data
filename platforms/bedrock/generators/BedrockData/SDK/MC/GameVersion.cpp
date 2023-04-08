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
