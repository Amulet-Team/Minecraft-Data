#include "BiomeRegistry.hpp"
#include "HookAPI.h"


using namespace MinecraftAPI;


BiomeRegistry::_forEachBiomeT BiomeRegistry::_forEachBiome = (BiomeRegistry::_forEachBiomeT)dlsym("?forEachBiome@BiomeRegistry@@QEBAXV?$function@$$A6AXAEAVBiome@@@Z@std@@@Z");
