#pragma once

#include "Block.hpp"
#include "BlockActor.hpp"
#include "BlockSource.hpp"

namespace MinecraftAPI {
	class Dimension {
		typedef BlockSource& (*_getBlockSourceFromMainChunkSourceT)(const Dimension*);
		static _getBlockSourceFromMainChunkSourceT _getBlockSourceFromMainChunkSource;
		
	public:
		BlockSource* getBlockSource();
		const Block* getBlock(int x, int y, int z);
		BlockActor* getBlockEntity(int x, int y, int z);
	};
}
