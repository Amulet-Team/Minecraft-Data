#pragma once
#include <string>
#include "../Global.h"
#include "BaseGameVersion.hpp"

class Item {
public:
	// ?getRequiredBaseGameVersion@Item@@QEBAAEBVBaseGameVersion@@XZ
	MCAPI BaseGameVersion const& getRequiredBaseGameVersion() const;
	// ?getId@Item@@QEBAFXZ
	MCAPI short getId() const;
	// ?getFullItemName@Item@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	MCAPI std::string const& getFullItemName() const;
};
