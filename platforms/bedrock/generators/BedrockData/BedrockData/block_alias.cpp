#pragma once
#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include "get_file.hpp"


THook(void, "?registerAlias@BlockTypeRegistry@@SAXAEBVHashedString@@0@Z", const HashedString& alias, const HashedString& name) {
    *getFile("generated/block/alias.txt") << alias.getString() << "|" << name.getString() << std::endl;
    original(alias, name);
}
