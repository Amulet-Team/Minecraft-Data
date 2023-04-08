#pragma once
#include "generators.hpp"

#include <MC/MobEffect.hpp>
#include "logging.hpp"

using namespace MinecraftAPI;


void Data::effect() {
	for (auto i = 0; i < 500; i++) {
		MobEffect* effect = MobEffect::getById(i);
		std::cout << i << " " << (effect == nullptr) << std::endl;
		if (effect != nullptr) {
			logToFile("generated/effect/input_id.txt", i);
			logToFile("generated/effect/name.txt", effect->getResourceName());
			logToFile("generated/effect/id.txt", effect->getId());
			logToFile("generated/effect/description_id.txt", effect->getDescriptionId());
//			*getFile("generated/effect/data/component.txt") << effect->getComponentName().getString() << std::endl;
//			auto colour = effect->getColor();
//			*getFile("generated/effect/data/colour.txt") << colour.r << "," << colour.g << "," << colour.b << "," << colour.a << std::endl;
		}
	}
}
