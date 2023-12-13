#pragma once
#include "pch.h"
#include <MC/BlockLegacy.hpp>
#include <MC/BlockActor.hpp>
#include <MC/Color.hpp>
#include <MC/BaseGameVersion.hpp>
#include <GetVirtual.hpp>
#include <iostream>

VirtualRegex getMapColourFinder("?getMapColor@", "@@MEBA?AVColor@mce@@XZ", "BlockLegacy");
typedef mce::Color (*getMapColourT)(const BlockLegacy*);


mce::Color BlockLegacy::callGetMapColor() const {
	auto getMapColour = (getMapColourT)getMapColourFinder.get((void***)this);
	std::cout << "getMapColor at " << getMapColour << std::endl;
	if (getMapColour != NULL) {
		return getMapColour(this);
	}
	throw "could not find getMapColor";
};
