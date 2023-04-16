#include "Block.hpp"
#include "HookAPI.h"

using namespace MinecraftAPI;

void* Block::vftable = dlsym("??_7Block@@6B@");
// Added 1.9.0.15
Block::_getFrictionT Block::_getFriction = (Block::_getFrictionT)dlsym("?getFriction@Block@@QEBAMXZ");
// Added 1.16.210.5
Block::_getSerializationIdT Block::_getSerializationId = (Block::_getSerializationIdT)dlsym("?getSerializationId@Block@@QEBAAEBVCompoundTag@@XZ");
Block::_isContainerBlockT Block::_isContainerBlock = (Block::_isContainerBlockT)dlsym("?isContainerBlock@Block@@QEBA_NXZ");
Block::_getBlockEntityTypeT Block::_getBlockEntityType = (Block::_getBlockEntityTypeT)dlsym("?getBlockEntityType@Block@@QEBA?AW4BlockActorType@@XZ");
