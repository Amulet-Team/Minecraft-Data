#pragma once
#pragma comment(lib, "LLPreLoader.lib")
#pragma comment(lib, "SDK.lib")
#include <Windows.h>
#include <iostream>
#include <string>

#include "util/get_file.hpp"
#include "generators/generators.hpp"


DWORD WINAPI MainThread(HMODULE hModule) {
    // print to the console that the DLL is running
    std::cout << "BedrockData.dll Injected" << std::endl;

    try {
        Data::main();
        *getFile("generated/success.txt") << "success" << std::endl;
    }
    catch (const std::string error) {
        *getFile("generated/err.txt") << error << std::endl;
    }

    // print to the console that we are done
    std::cout << "Data generation finished." << std::endl;

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
