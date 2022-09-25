#pragma once
#include "pch.h"

#include <string>
#include <regex>

#include <HookAPI.h>
#include "dlsym.hpp"


std::regex specialChars{ R"([[\^$.|?*+(){}])" };
// Escape a regex string. I don't know why this isn't built in.
std::string escape(std::string s) {
	return std::regex_replace(s, specialChars, R"(\$&)");
}


VirtualRegex::VirtualRegex(std::string descriptor_prefix, std::string descriptor_suffix, std::string descriptor_base) {
	this->descriptor_prefix = descriptor_prefix;
	this->descriptor_suffix = descriptor_suffix;
	this->descriptor_base = descriptor_base;
	this->pattern = std::regex(escape(descriptor_prefix) + "[a-zA-Z0-9]+" + escape(descriptor_suffix));
};


// Get a pointer to the virtual function for the given object. obj is a pointer to an object with a virtual pointer as the first attribute.
void* VirtualRegex::get(void*** obj_ptr) {
	std::string baseDefinition = descriptor_prefix + descriptor_base + descriptor_suffix;
	if (dlsym_real(baseDefinition.c_str()) == NULL) {
		// If the base definition does not exist then something is wrong
		return NULL;
	}

	void** vtable_ptr = *obj_ptr;
	for (auto i = 0; i < 1000; i++) {
		void* func_ptr = *(vtable_ptr + i * sizeof(size_t));
		std::vector<std::string> names = dlsym_reverse((int)func_ptr);
		for (auto &name: names) {
			if (name.substr(0, 12) == "?getMapColor") {
				std::cout << name << " at index " << i << std::endl;
			}
			if (std::regex_match(name, pattern)) {
				std::cout << "found virtual function " << name << " at index " << i << " for " << baseDefinition << std::endl;
				//return func_ptr;
			}
		}
	}
	return NULL;
};
