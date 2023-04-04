#include "GameVersion.hpp"
#include "HookAPI.h"

using namespace MinecraftAPI;

int* GameVersion::_major = (int*)dlsym("?MajorVersion@SharedConstants@@3HB");
int* GameVersion::_minor = (int*)dlsym("?MinorVersion@SharedConstants@@3HB");
int* GameVersion::_patch = (int*)dlsym("?PatchVersion@SharedConstants@@3HB");
int* GameVersion::_revision = (int*)dlsym("?RevisionVersion@SharedConstants@@3HB");
