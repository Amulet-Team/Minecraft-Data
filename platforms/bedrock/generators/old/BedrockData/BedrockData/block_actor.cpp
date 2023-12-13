#pragma once
#include "pch.h"

#include <map>
#include <string>
#include <HookAPI.h>
#include "minecraft.hpp"
#include "get_file.hpp"


typedef std::map<enum BlockActorType, std::string> blockMapT;


void block_actor(Minecraft_* minecraft) {
    auto blockMapPtr = (blockMapT*)dlsym("?mClassIdMap@BlockActor@@0V?$map@W4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@W4BlockActorType@@@3@V?$allocator@U?$pair@$$CBW4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@3@@std@@B");
    if (blockMapPtr != NULL) {
        std::map<enum BlockActorType, std::string>::iterator it;
        for (it = blockMapPtr->begin(); it != blockMapPtr->end(); ++it) {
            *getFile("generated/block/actor_map.txt") << it->first << "|" << it->second << std::endl;
        }
    } else {
        *getFile("generated/err.txt") << "?mClassIdMap@BlockActor@@0V?$map@W4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@W4BlockActorType@@@3@V?$allocator@U?$pair@$$CBW4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@3@@std@@B" << std::endl;
    }
}
