#pragma once
#include "pch.h"
#include <string>

#include "get_file.hpp"

class SemVersion_ {
public:
	std::string const& asString() const;
};


std::string const& SemVersion_::asString() const {
	typedef const std::string& (*t_asStringOriginal)(const SemVersion_*);
	auto asStringOriginal = (t_asStringOriginal)dlsym("?asString@SemVersion@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	if (asStringOriginal == NULL) {
		*getFile("generated/err.txt") << "?asString@SemVersion@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ" << std::endl;
		return "null";
	}
	else {
		return asStringOriginal(this);
	}
}
