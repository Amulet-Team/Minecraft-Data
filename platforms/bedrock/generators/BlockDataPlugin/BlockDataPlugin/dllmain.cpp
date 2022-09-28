// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#include "pch.h"
#pragma comment(lib, "bedrock_server_api.lib")
#pragma comment(lib, "bedrock_server_var.lib")
#pragma comment(lib, "../LiteLoaderSDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../../LLPreLoader/LLPreLoader.lib")

#include <fstream>
#include <Windows.h>
#include <MC/Level.hpp>
#include <MC/NbtIo.hpp>
#include <MC/CompoundTag.hpp>
#include <MC/BlockActor.hpp>
#include <MC/BlockPos.hpp>
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


std::string lastValue = "";



TInstanceHook(void, "?tick@Level@@UEAAXXZ", Level) {
    Dimension* dim = this->getDimension(0);
    if (dim != NULL) {
        BlockSource* blockSource = &dim->getBlockSourceFromMainChunkSource();
        BlockActor* blockActor = blockSource->getBlockEntity(100, 100, 100);
        if (blockActor == NULL) {
            lastValue = "";
        }
        else {
            auto compound = CompoundTag::fromBlockActor(blockActor);
            std::string out = write_compound(compound.get());
            if (lastValue != out) {
                lastValue = out;
                std::ofstream file ("block_entity.nbt", std::ios::binary);
                file << out;
                std::cout << "nbt changed" << std::endl;
            }
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
