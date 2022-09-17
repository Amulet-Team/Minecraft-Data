#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include <MC/BaseGameVersion.hpp>
#include <MC/Item.hpp>
#include "get_file.hpp"


THook(void, "?registerAlias@ItemRegistry@@SAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z", const HashedString& alias, const HashedString& name, const BaseGameVersion& game_version) {
    *getFile("generated/item/alias.txt") << alias.getString() << "|" << name.getString() << "|" << game_version.asSemVersion().asString() << std::endl;
    original(alias, name, game_version);
}


THook(Item&, "?registerComplexAlias@ItemRegistry@@SAAEAVItem@@AEBVHashedString@@V?$function@$$A6A?AVHashedString@@F@Z@std@@@Z", const HashedString& alias, std::function<HashedString(short)> func) {
	for (auto i = 0; i < 256; i++) {
		HashedString name = func(i);
		*getFile("generated/item/complex_alias.txt") << alias.getString() << "|" << i << "|" << name.getString() << std::endl;
	}
	return original(alias, func);
}

THook(void, "?registerLegacyID@ItemRegistry@@SAXAEBVHashedString@@F@Z", const HashedString& name, short id) {
	*getFile("generated/item/legacy_id.txt") << id << "|" << name.getString() << std::endl;
	original(name, id);
}

THook(void, "?registerLegacyMapping@ItemRegistry@@SAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z", const HashedString& alias, const HashedString& name, const BaseGameVersion& game_version) {
	*getFile("generated/item/legacy_mapping.txt") << alias.getString() << "|" << name.getString() << "|" << game_version.asSemVersion().asString() << std::endl;
	original(alias, name, game_version);
}
