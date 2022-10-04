#pragma once
#include "../Global.h"
#include <string>

class HashedString {
public:
	// ?getString@HashedString@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	MCAPI std::string const& getString() const;
};
