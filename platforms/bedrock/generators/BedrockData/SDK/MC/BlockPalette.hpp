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

/*
001.009.000.015_added.hpp
	?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBVCompoundTag@@@Z
	?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z
	?getBlockFromLegacyData@BlockPalette@@QEBAAEBVBlock@@UNewBlockID@@I@Z
	?getBlockLegacy@BlockPalette@@QEBAPEBVBlockLegacy@@AEBVCompoundTag@@@Z
	?getBlockLegacy@BlockPalette@@QEBAPEBVBlockLegacy@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	?initFromBlockDefinitions@BlockPalette@@QEAAXXZ
	?shouldWarnFor@BlockPalette@@AEBA_NUNewBlockID@@E@Z
	?switchBlock@BlockPalette@@QEBAAEBVBlock@@AEBV2@0@Z
	?tryGetBlock@BlockPalette@@QEBAPEBVBlock@@AEBVCompoundTag@@@Z
001.011.000.023_removed.hpp
	?switchBlock@BlockPalette@@QEBAAEBVBlock@@AEBV2@0@Z
001.012.000.028_added.hpp
	?shouldWarnFor@BlockPalette@@AEBA_NUNewBlockID@@G@Z
	?switchBlock@BlockPalette@@QEBAAEBVBlock@@AEBV2@AEBVBlockLegacy@@@Z
001.012.000.028_removed.hpp
	?shouldWarnFor@BlockPalette@@AEBA_NUNewBlockID@@E@Z
001.013.000.034_removed.hpp (2 hits)
	?getBlockLegacy@BlockPalette@@QEBAPEBVBlockLegacy@@AEBVCompoundTag@@@Z
	?tryGetBlock@BlockPalette@@QEBAPEBVBlock@@AEBVCompoundTag@@@Z
001.016.000.002_added.hpp
	?convertLegacyBlocks@BlockPalette@@QEBA_NV?$buffer_span_mut@PEBVBlock@@@@V?$buffer_span@UBlockID@@@@V?$buffer_span@UNibblePair@@@@_K@Z
001.016.001.002_removed.hpp
	?convertLegacyBlocks@BlockPalette@@QEBA_NV?$buffer_span_mut@PEBVBlock@@@@V?$buffer_span@UBlockID@@@@V?$buffer_span@UNibblePair@@@@_K@Z
001.016.100.004_removed.hpp
	?initFromBlockDefinitions@BlockPalette@@QEAAXXZ
001.016.210.005_added.hpp
	?convertLegacyBlock@BlockPalette@@QEBAAEBVBlock@@UBlockID@@G@Z
	?convertLegacyBlocks@BlockPalette@@QEBA_NV?$buffer_span_mut@PEBVBlock@@@@V?$buffer_span@UBlockID@@@@V?$buffer_span@UNibblePair@@@@_K@Z
	?initFromBlockDefinitions@BlockPalette@@QEAAXXZ
001.017.000.003_added.hpp
	?cacheBlockComponentData@BlockPalette@@QEAAXXZ
 */