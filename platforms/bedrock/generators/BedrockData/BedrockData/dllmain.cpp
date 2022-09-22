// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#include "pch.h"
#pragma comment(lib, "bedrock_server_api.lib")
#pragma comment(lib, "bedrock_server_var.lib")
#pragma comment(lib, "../LiteLoaderSDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../LLPreLoader/LLPreLoader.lib")

#include "minecraft.hpp"
#include "get_file.hpp"


void biome(Minecraft_*);
void block(Minecraft_*);
void effect(Minecraft_*);
void item();
void version();


void data_main(Minecraft_* minecraft) {
    biome(minecraft);
    block(minecraft);
    effect(minecraft);
    item();
    version();
}


DWORD WINAPI MainThread(HMODULE hModule) {
    // print to the console that the DLL is running
    std::cout << "BDSdll Injected" << std::endl;
    
    // Get the Minecraft instance
    Minecraft_** minecraft = (Minecraft_**)dlsym("?mGame@ServerCommand@@1PEAVMinecraft@@EA");
    if (minecraft == NULL) {
        *getFile("generated/err.txt") << "?mGame@ServerCommand@@1PEAVMinecraft@@EA" << std::endl;
    } else {
        while (*minecraft == NULL) {
            // This is not set until the server is set up so wait until it is ready
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        std::cout << "minecraft" << minecraft << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "minecraft at: " << minecraft << std::endl;
        data_main(*minecraft);
    }

    // print to the console that we are done
    std::cout << "Data generation finished." << std::endl;

    // run normal termination by closing the window
    auto window = GetConsoleWindow();
    PostMessage(window, WM_CLOSE, 0, 0);

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
