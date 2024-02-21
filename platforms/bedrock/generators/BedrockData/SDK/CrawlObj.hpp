#pragma once

#include "HookAPI.h"
#include "logging.hpp"
#include "set"


class ObjectCrawler {
private:
	size_t depth;
	size_t max_depth;
	int max_off;
	std::set<void*> parents;

	std::string getIndent();
	void crawl(void** obj);

public:
	ObjectCrawler(void** obj, int max_off = 100, size_t max_depth = 5): max_off(max_off), max_depth(max_depth) {
		depth = 0;
		crawl(obj);
	};
};
