#include "MobEffect.hpp"
#include <iostream>
#include "HookAPI.h"

using namespace MinecraftAPI;

MobEffect* (*MobEffect::getById)(int) = (MobEffect * (*)(int))dlsym("?getById@MobEffect@@SAPEAV1@H@Z");
std::string const& (*MobEffect::getResourceName)(MobEffect*) = (std::string const& (*)(MobEffect*))dlsym("?getResourceName@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
