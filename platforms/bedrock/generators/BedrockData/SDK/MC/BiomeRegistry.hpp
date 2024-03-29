#pragma once
#include "Biome.hpp"
#include <functional>
#include "logging.hpp"
#include <string>


namespace MinecraftAPI {
	class BiomeRegistry {
		// 1.9.0.15
		typedef void (*_forEachBiomeT)(const BiomeRegistry*, std::function<void(Biome&)>);
		static _forEachBiomeT _forEachBiome;

	public:
		void forEachBiome(std::function<void(Biome&)> callback) const {
			if (_forEachBiome){
				_forEachBiome(this, callback);
			}
		};
	};
}
