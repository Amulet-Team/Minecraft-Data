#include "BlockSource.hpp"
#include "HookAPI.h"
#include <stdexcept>

using namespace MinecraftAPI;


BlockSource::_getBlockT BlockSource::_getBlock = (BlockSource::_getBlockT)dlsym("?getBlock@BlockSource@@QEBAAEBVBlock@@HHH@Z");
BlockSource::_getBlockEntityT BlockSource::_getBlockEntity = (BlockSource::_getBlockEntityT)dlsym("?getBlockEntity@BlockSource@@QEAAPEAVBlockActor@@HHH@Z");


const Block* BlockSource::getBlock(int x, int y, int z) {
	if (_getBlock) {
		return &_getBlock(this, x, y, z);
	}
	if (_getBlockT _getBlock = findVirtual<_getBlockT, const BlockSource>(this, "?getBlock@BlockSource@@UEBAAEBVBlock@@HHH@Z", 100)) {
		return &_getBlock(this, x, y, z);
	}
	throw std::runtime_error("Could not find BlockSource::getBlock");
};


BlockActor* BlockSource::getBlockEntity(int x, int y, int z) {
	if (_getBlockEntity) {
		return _getBlockEntity(this, x, y, z);
	}
	throw std::runtime_error("Could not find BlockSource::getBlockEntity");
};
