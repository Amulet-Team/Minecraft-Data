// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#include "pch.h"
#pragma comment(lib, "bedrock_server_api.lib")
#pragma comment(lib, "bedrock_server_var.lib")
#pragma comment(lib, "SymDBHelper.lib")
#pragma comment(lib, "LLPreLoader.lib")

#include <fstream>
#include <Windows.h>
#include <MC/Level.hpp>
#include <MC/NbtIo.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/BlockActor.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Dimension.hpp>
#include <HookAPI.h>


std::unique_ptr<CompoundTag> CompoundTag::create() {
    return std::unique_ptr<CompoundTag>((CompoundTag*)Tag::newTag(Tag::Type::Compound).release());
}


std::unique_ptr<CompoundTag> CompoundTag::fromBlockActor(BlockActor* blockActor) {
    auto tag = CompoundTag::create();
    blockActor->save(*tag);
    return std::move(tag);
}


std::string write_compound(const CompoundTag* tag) {
    void* vtbl = dlsym("??_7StringByteOutput@@6B@");
    string result = "";
    void* iDataOutput[2] = { vtbl, &result };
    NbtIo::write(tag, (IDataOutput&)iDataOutput);
    return result;
}

using namespace std::string_literals;
std::string lastBlockStr = "";
std::string lastBlockEntityStr = "";
std::string empty = "\x01\x00\x00\x00"s;



TInstanceHook(void, "?tick@Level@@UEAAXXZ", Level) {
    Dimension* dim = this->getDimension(0);
    if (dim != NULL) {
        BlockSource* blockSource = &dim->getBlockSourceFromMainChunkSource();
        bool changed = false;
        const Block* block = &blockSource->getBlock(100, 100, 100);
        if (block == NULL) {
            if (lastBlockStr != empty) {
                lastBlockStr = empty;
                changed = true;
            };
        }
        else {
            const CompoundTag* tag = &block->getSerializationId();
            std::string blockStr = write_compound(tag);
            if (lastBlockStr != blockStr) {
                lastBlockStr = blockStr;
                changed = true;
            }
        }
        
        BlockActor* blockActor = blockSource->getBlockEntity(100, 100, 100);
        if (blockActor == NULL) {
            if (lastBlockEntityStr != empty) {
                lastBlockEntityStr = empty;
                changed = true;
            };
        }
        else {
            auto compound = CompoundTag::fromBlockActor(blockActor);
            std::string blockEntityStr = write_compound(compound.get());
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
        }
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
