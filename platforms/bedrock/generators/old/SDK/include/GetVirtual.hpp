#pragma once

#include <string>
#include <regex>


// A virtual regex container
class VirtualRegex {
public:
	VirtualRegex() = delete;
	VirtualRegex(std::string descriptor_prefix, std::string descriptor_suffix, std::string descriptor_base);
	std::string descriptor_prefix;
	std::string descriptor_suffix;
	std::string descriptor_base;
	std::regex pattern;
	void* get(void*** obj_ptr);
};
