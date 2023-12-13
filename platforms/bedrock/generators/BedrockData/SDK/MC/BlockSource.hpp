#pragma once
#include "Block.hpp"
#include "BlockActor.hpp"

namespace MinecraftAPI {
	class BlockSource {
		typedef const Block& (*_getBlockT)(const BlockSource*, int, int, int);
		static _getBlockT _getBlock;
		typedef BlockActor* (*_getBlockEntityT)(const BlockSource*, int, int, int);
		static _getBlockEntityT _getBlockEntity;

	public:
		const Block* getBlock(int, int, int);
		BlockActor* getBlockEntity(int, int, int);
	};
}
