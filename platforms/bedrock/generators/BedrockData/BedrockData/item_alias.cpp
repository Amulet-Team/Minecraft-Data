#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include <MC/BaseGameVersion.hpp>
#include "get_file.hpp"


THook(void, "?registerAlias@ItemRegistry@@SAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z", const HashedString& alias, const HashedString& name, const BaseGameVersion& game_version) {
    *getFile("generated/item/alias.txt") << alias.getString() << "|" << name.getString() << std::endl;
    original(alias, name, game_version);
}
