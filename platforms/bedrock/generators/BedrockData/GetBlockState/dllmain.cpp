#pragma once
#pragma comment(lib, "LLPreLoader.lib")
#pragma comment(lib, "SDK.lib")
#include <Windows.h>
#include <string>

#include "logging.hpp"
#include "MC/Minecraft.hpp"
#include "MC/nbt/NbtIo.hpp"
#include "MC/Dimension.hpp"

using namespace MinecraftAPI;


DWORD WINAPI MainThread(HMODULE hModule) {
    // print to the console that the DLL is running
    debug("GetBlockState.dll Injected");

    Minecraft* minecraft = Minecraft::get();
    while (true) {
        if (Level* level = minecraft->getLevel()) {
            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
        if (BlockPalette* block_palette = level->getBlockPalette()) {
            unsigned int palette_len = block_palette->len();
            debug("There are " + std::to_string(palette_len) + " blocks in the palette.");
            for (unsigned int i = 0; i < palette_len; i++) {
                const Block* block = block_palette->getBlock(i);
                //logToFile("generated/block/data/friction.txt", block->getFriction());
                const CompoundTag* tag = block->getSerializationId();
                std::string tag_data = NbtIo::serialise(tag);
                logToBinaryFile("generated/block/states.nbtarr", tag_data);
                logToFile("generated/block/is_container.txt", block->isContainerBlock());
                logToFile("generated/block/block_entity.txt", block->getBlockEntityType());
                logToFile("generated/block/variant.txt", block->getVariant());
            }
        }
        else {
            debug("Could not find block palette");
        }
    }

    // return because the function declarion requires it
    return 0;
}


BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
