#pragma once
#include <string>
//#include "Global.h"
//#include "Color.hpp"
//#include "HashedString.hpp"


namespace MinecraftAPI {
	class MobEffect {
	public:
		static MobEffect* (*getById)(int);
		static std::string const& (*getResourceName)(MobEffect*);
	//public:
	//    enum class EffectType : short {};
	//    // ?getById@MobEffect@@SAPEAV1@H@Z
	//    MCAPI static MobEffect* getById(int);
	//    // ?getResourceName@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	//    MCAPI std::string const& getResourceName() const;
	//    // ?getId@MobEffect@@QEBAIXZ
	//    MCAPI unsigned int getId() const;
	//    // ?getDescriptionId@MobEffect@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	//    MCAPI std::string const& getDescriptionId() const;
	//    // ?getComponentName@MobEffect@@QEBAAEBVHashedString@@XZ
	//    MCAPI HashedString const& getComponentName() const;
	//    // ?getColor@MobEffect@@QEBAAEBVColor@mce@@XZ
	//    MCAPI mce::Color const& getColor() const;
	};
}
