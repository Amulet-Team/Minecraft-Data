#pragma once

#include "Block.hpp"


namespace MinecraftAPI {
	class BlockPalette {
		typedef Block const& (*_getBlockT)(const BlockPalette*, unsigned int const&);
		static _getBlockT _getBlock;

	public:
		Block const* getBlock(unsigned int id) {
			if (_getBlock) {
				return &_getBlock(this, id);
			}
			return nullptr;
		};

		unsigned int len();
	};
}
