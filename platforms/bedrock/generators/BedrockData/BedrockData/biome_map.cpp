#pragma once
#include "pch.h"

#include <fstream>
#include <string>

#include "minecraft.hpp"
#include "get_file.hpp"


std::map<void*, int> biomeMap = {};


// init function
TInstanceHook(void, "??0Biome@@QEAA@H@Z", Biome_, int biome_id) {
	biomeMap[this] = biome_id;
	original(this, biome_id);
}


// setName function
TInstanceHook(Biome_&, "?setName@Biome@@QEAAAEAV1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z", Biome_, std::string biome_name) {
	auto i = biomeMap.find(this);
	if (i == biomeMap.end()) {
		*getFile("generated/err.txt") << "Biome not in biomeMap: " << this << " " << biome_name << std::endl;
	} else {
		auto biome_id = biomeMap.extract(this).mapped();
		*getFile("generated/biome/biome_map.txt") << biome_id << "|" << biome_name << std::endl;
	}
	return original(this, biome_name);
}


void biome_map() {
	if (dlsym("??0Biome@@QEAA@H@Z") == NULL) {
		*getFile("generated/err.txt") << "??0Biome@@QEAA@H@Z" << std::endl;
	}
	if (dlsym("?setName@Biome@@QEAAAEAV1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z") == NULL) {
		*getFile("generated/err.txt") << "?setName@Biome@@QEAAAEAV1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z" << std::endl;
	}
	for (auto it = biomeMap.begin(); it != biomeMap.end(); it++) {
		*getFile("generated/err.txt") << "biome created with no name: " << it->second << std::endl;
	}
}
