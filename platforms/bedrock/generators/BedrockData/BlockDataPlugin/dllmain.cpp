// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#pragma comment(lib, "LLPreLoader.lib")
#pragma comment(lib, "SDK.lib")

#include <fstream>
#include <Windows.h>
#include <memory>

#include <MC/Level.hpp>
#include <MC/nbt/NbtIo.hpp>
#include <MC/nbt/Tag.hpp>
#include <MC/nbt/CompoundTag.hpp>
#include <MC/BlockActor.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Dimension.hpp>
#include <HookAPI.h>

using namespace MinecraftAPI;


std::unique_ptr<CompoundTag> CompoundTagfromBlockActor(BlockActor* blockActor) {
    auto tag = CompoundTag::create();
    blockActor->save(*tag);
    return std::move(tag);
}

using namespace std::string_literals;
std::string lastBlockStr = "";
std::string lastBlockEntityStr = "";
std::string empty = "\x01\x00\x00\x00"s;



TInstanceHook(void, "?tick@Level@@UEAAXXZ", Level) {
    std::cout << "tick" << std::endl;
    try {
        if (Dimension* dim = this->getDimension(0)) {
            //BlockSource* blockSource = &dim->getBlockSourceFromMainChunkSource();
            //const Block* block = &blockSource->getBlock(100, 100, 100);
            //BlockActor* blockActor = blockSource->getBlockEntity(100, 100, 100);

            std::cout << "got dimension" << std::endl;

            /*bool changed = false;
            const Block* block = dim->getBlock(100, 100, 100);
            if (block == NULL) {
                if (lastBlockStr != empty) {
                    lastBlockStr = empty;
                    changed = true;
                };
            }
            else {
                const CompoundTag* tag = block->getSerializationId();
                std::string blockStr = NbtIo::serialise(tag);
                if (lastBlockStr != blockStr) {
                    lastBlockStr = blockStr;
                    changed = true;
                }
            }

            BlockActor* blockActor = dim->getBlockEntity(100, 100, 100);
            if (blockActor == NULL) {
                if (lastBlockEntityStr != empty) {
                    lastBlockEntityStr = empty;
                    changed = true;
                };
            }
            else {
                auto compound = CompoundTagfromBlockActor(blockActor);
                std::string blockEntityStr = NbtIo::serialise(compound.get());
                if (lastBlockEntityStr != blockEntityStr) {
                    lastBlockEntityStr = blockEntityStr;
                    changed = true;
                }
            }

            if (changed) {
                std::ofstream file("block_data.nbt", std::ios::binary);
                file << lastBlockStr;
                file << lastBlockEntityStr;
                std::cout << "block changed" << std::endl;
            }*/
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    original(this);
}


BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
