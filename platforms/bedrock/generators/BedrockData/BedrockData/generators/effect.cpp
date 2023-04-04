#pragma once
#include "generators.hpp"

#include <MC/MobEffect.hpp>
//#include <MC/HashedString.hpp>
//#include "data_generator/get_file.hpp"

using namespace MinecraftAPI;


void Data::effect() {
	for (auto i = 0; i < 500; i++) {
		MobEffect* effect = MobEffect::getById(i);
//		if (effect != NULL) {
////			*getFile("generated/effect/data/name.txt") << effect->getResourceName() << std::endl;
////			*getFile("generated/effect/data/id.txt") << effect->getId() << std::endl;
////			*getFile("generated/effect/data/description.txt") << effect->getDescriptionId() << std::endl;
////			*getFile("generated/effect/data/component.txt") << effect->getComponentName().getString() << std::endl;
////			auto colour = effect->getColor();
////			*getFile("generated/effect/data/colour.txt") << colour.r << "," << colour.g << "," << colour.b << "," << colour.a << std::endl;
//		}
	}
}
