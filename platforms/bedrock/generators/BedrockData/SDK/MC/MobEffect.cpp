#include "MobEffect.hpp"
#include <iostream>
#include "HookAPI.h"

using namespace MinecraftAPI;

// Added 1.9.0.15
MobEffect::_getByIdT MobEffect::_getById = (MobEffect::_getByIdT)dlsym("?getById@MobEffect@@SAPEAV1@H@Z");
// Added 1.16.210.5
MobEffect::_getResourceNameT MobEffect::_getResourceName = (MobEffect::_getResourceNameT)dlsym("?getResourceName@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
// Added 1.16.210.5
MobEffect::_getIdT MobEffect::_getId = (MobEffect::_getIdT)dlsym("?getId@MobEffect@@QEBAIXZ");
// Added 1.16.210.5
MobEffect::_getDescriptionIdT MobEffect::_getDescriptionId = (MobEffect::_getDescriptionIdT)dlsym("?getDescriptionId@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
