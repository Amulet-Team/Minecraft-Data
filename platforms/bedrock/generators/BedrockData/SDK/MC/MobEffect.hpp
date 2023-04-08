#pragma once
#include <string>


namespace MinecraftAPI {
	class MobEffect;
	class MobEffect {
		typedef MobEffect* (*_getByIdT)(int);
		static _getByIdT _getById;

		typedef MobEffect* (*_getById1940T)(unsigned int);
		static _getById1940T _getById1940;

		typedef std::string const& (*_getResourceNameT)(const MobEffect*);
		static _getResourceNameT _getResourceName;

		typedef unsigned int (*_getIdT)(const MobEffect*);
		static _getIdT _getId;

		typedef std::string const& (*_getDescriptionIdT)(const MobEffect*);
		static _getDescriptionIdT _getDescriptionId;

	public:
		static MobEffect* getById(int id) {
			if (_getById1940 != nullptr) {
				return _getById1940(id);
			}
			else if (_getById != nullptr) {
				return _getById(id);
			}
			return nullptr;
		}

		std::string const& getResourceName() {
			if (_getResourceName != nullptr) {
				return _getResourceName(this);
			}
			return "";
		};

		unsigned int getId() const {
			if (_getId != nullptr) {
				return _getId(this);
			}
			return -1;
		};

		std::string const& getDescriptionId() {
			if (_getDescriptionId != nullptr) {
				return _getDescriptionId(this);
			}
			return "";
		};
	};
}
	
//  001.009.000.015_added.hpp
//	?mMobEffects@MobEffect@@2PAV?$unique_ptr@VMobEffect@@U?$default_delete@VMobEffect@@@std@@@std@@A

//  001.016.210.005_added.hpp
//	?getComponentName@MobEffect@@QEBAAEBVHashedString@@XZ
//	?getDescriptionId@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
//	?getDurationModifier@MobEffect@@QEBAMXZ
//	?getId@MobEffect@@QEBAIXZ
//	?getResourceName@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ

//  001.018.030.004_removed.hpp
//	?getComponentName@MobEffect@@QEBAAEBVHashedString@@XZ

//  001.018.032.002_added.hpp
//	?getColor@MobEffect@@QEBAAEBVColor@mce@@XZ
//	?getComponentName@MobEffect@@QEBAAEBVHashedString@@XZ
