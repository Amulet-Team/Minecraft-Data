#pragma once
#include "pch.h"

#include "minecraft.hpp"
#include "get_file.hpp"


void block_actor(Minecraft_* minecraft) {
    auto blockMapPtr = dlsym("?mClassIdMap@BlockActor@@0V?$map@W4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@W4BlockActorType@@@3@V?$allocator@U?$pair@$$CBW4BlockActorType@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@3@@std@@B");
    auto& blockMap = *reinterpret_cast<std::map<enum BlockActorType, std::string>*>(blockMapPtr);
    getFile("generated/block/actor_map.txt");
    map<enum BlockActorType, std::string>::iterator it;
    for (it = blockMap.begin(); it != blockMap.end(); ++it) {
        *getFile("generated/block/actor_map.txt") << it->first << "|" << it->second << std::endl;
    }
}
