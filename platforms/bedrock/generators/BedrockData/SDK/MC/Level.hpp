#pragma once

#include "BlockPalette.hpp"
#include "BiomeRegistry.hpp"
#include "Dimension.hpp"
#include "AutomaticID.hpp"
#include "Ref.hpp"
#include <HookAPI.h>
#include <stdexcept>


namespace MinecraftAPI {
	class Level {
		// ?getBlockPalette@Level@@UEAAAEAVBlockPalette@@XZ
		typedef BlockPalette& (*_getBlockPaletteT)(Level*);
		// ?getBlockPalette@Level@@UEBAAEBVBlockPalette@@XZ
		//typedef BlockPalette const& _getBlockPaletteT(const Level*);

		typedef BiomeRegistry const& (*_getBiomeRegistryT)(const Level*);

		typedef Dimension* (*_getDimensionT)(const Level*, AutomaticID<Dimension, int>);
		static _getDimensionT _getDimension;
		typedef WeakRefT<struct SharePtrRefTraits<class Dimension>>(*_getDimension3T)(const Level*, AutomaticID<Dimension, int>);

	public:
		BlockPalette* getBlockPalette();
		const BiomeRegistry* getBiomeRegistry() const;
		Dimension* getDimension(int dimension) const {
			if (_getDimension) {
				return _getDimension(this, AutomaticID<Dimension, int>(dimension));
			}
			if (_getDimensionT _getDimension2 = findVirtual<_getDimensionT, const Level>(this, "?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z", 100)) {
				return _getDimension2(this, AutomaticID<Dimension, int>(dimension));
			}
			if (_getDimension3T _getDimension3 = findVirtual<_getDimension3T, const Level>(this, "?getDimension@Level@@UEBA?AV?$WeakRefT@U?$SharePtrRefTraits@VDimension@@@@@@V?$AutomaticID@VDimension@@H@@@Z", 100)) {
				auto id = AutomaticID<Dimension, int>(dimension);
				std::cout << "got virtual 2" << std::endl;
				return _getDimension3(this, id).get();
			}
			throw std::runtime_error("Could not find Level::getDimension");
		};
	};
}
