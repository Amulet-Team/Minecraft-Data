#include "Dimension.hpp"
#include "HookAPI.h"
#include <stdexcept>


using namespace MinecraftAPI;


Dimension::_getBlockSourceFromMainChunkSourceT Dimension::_getBlockSourceFromMainChunkSource = (Dimension::_getBlockSourceFromMainChunkSourceT)dlsym("?getBlockSourceFromMainChunkSource@Dimension@@QEBAAEAVBlockSource@@XZ");

BlockSource* Dimension::getBlockSource() {
	if (_getBlockSourceFromMainChunkSource) {
		return &_getBlockSourceFromMainChunkSource(this);
	}
	throw std::runtime_error("Could not get block source");
};

const Block* Dimension::getBlock(int x, int y, int z) {
	BlockSource* blockSource = this->getBlockSource();
	return blockSource->getBlock(x, y, z);
};

BlockActor* Dimension::getBlockEntity(int x, int y, int z) {
	BlockSource* blockSource = this->getBlockSource();
	return blockSource->getBlockEntity(x, y, z);
};
