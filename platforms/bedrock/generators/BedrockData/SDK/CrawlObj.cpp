#pragma once

#include "CrawlObj.hpp"


std::string ObjectCrawler::getIndent() {
	return std::string(depth, 9);
}

void ObjectCrawler::crawl(void** obj) {
	if (parents.count(obj)) {
		//debug(getIndent() + std::to_string((uintptr_t)obj) + " has already been processed.");
		return;
	}
	if (depth+1 > max_depth) {
		//debug(getIndent() + std::to_string((uintptr_t)obj) + " Max depth exceeded.");
		return;
	}
	std::vector<std::string> symbols = dlsym_reverse((int)obj);
	if (symbols.empty()) {
		debug(getIndent() + std::to_string((uintptr_t)obj));
	}
	else {
		bool isVtable = false;
		std::string symbols_str = " ";
		for (std::string symbol : symbols) {
			if (symbol.rfind("??_7", 0) == 0) {
				isVtable = true;
			}
			symbols_str += symbol;
		}
		debug(getIndent() + std::to_string((uintptr_t)obj) + symbols_str);
		if (isVtable) {
			return;
		}
	}
	parents.insert(obj);
	depth += 1;
	for (int off = 0; off < max_off; off++) {
		void** attr_ptr = obj + off;
		if (isGoodReadPtr(attr_ptr)) {
			void* attr = *attr_ptr;
			if (isGoodReadPtr(attr)) {
				crawl((void**)attr);
			}
			else {
				//debug(getIndent() + std::to_string((uintptr_t)attr_ptr) + " Non-pointer data or nullptr.");
			}
		}
		else {
			// Read beyond the data block.
			break;
		}
	}
	depth -= 1;
};
