#pragma once
#include "../Global.h"
#include "SemVersion.hpp"

class BaseGameVersion {
public:
	// ?asSemVersion@BaseGameVersion@@QEBAAEBVSemVersion@@XZ
	MCAPI SemVersion const& asSemVersion() const;
};
