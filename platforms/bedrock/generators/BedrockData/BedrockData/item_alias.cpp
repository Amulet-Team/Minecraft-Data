#include "pch.h"

#include <fstream>
#include <string>

#include <MC/HashedString.hpp>
#include <MC/BaseGameVersion.hpp>
#include <MC/Item.hpp>
#include "get_file.hpp"


THook(void, "?registerAlias@ItemRegistry@@SAXAEBVHashedString@@0AEBVBaseGameVersion@@@Z", const HashedString& alias, const HashedString& name, const BaseGameVersion& game_version) {
    *getFile("generated/item/alias.txt") << alias.getString() << "|" << name.getString() << std::endl;
    original(alias, name, game_version);
}


THook(Item&, "?registerComplexAlias@ItemRegistry@@SAAEAVItem@@AEBVHashedString@@V?$function@$$A6A?AVHashedString@@F@Z@std@@@Z", const HashedString& alias, std::function<HashedString(short)> func) {
	std::function<HashedString(short)> func_wrap = [alias, func](signed short data) {
		HashedString str = func(data);
		*getFile("generated/item/complex_alias.txt") << alias.getString() << "|" << data << "|" << str.getString() << std::endl;
		return str;
	};
	return original(alias, func_wrap);
}
