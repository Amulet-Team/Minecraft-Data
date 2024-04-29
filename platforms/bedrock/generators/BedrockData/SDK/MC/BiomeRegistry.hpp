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

		// 1.16.0.2
		typedef Biome* (*_lookupByIdT)(const BiomeRegistry*, int);
		static _lookupByIdT _lookupById;

	public:
		void forEachBiome(std::function<void(Biome&)> callback) const {
			if (_forEachBiome){
				_forEachBiome(this, callback);
			}
		};

		Biome* lookupById(int id) const {
			if (_lookupById) {
				return _lookupById(this, id);
			}
			return nullptr;
		};
	};
}
