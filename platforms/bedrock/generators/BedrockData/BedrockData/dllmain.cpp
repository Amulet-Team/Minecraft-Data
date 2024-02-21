#pragma once
#pragma comment(lib, "LLPreLoader.lib")
#pragma comment(lib, "SDK.lib")
#include <Windows.h>
#include <string>

#include "logging.hpp"
#include "generators/generators.hpp"


DWORD WINAPI MainThread(HMODULE hModule) {
    // print to the console that the DLL is running
    debug("BedrockData.dll Injected");

    try {
        Data::main();
        debug("Data generation finished successfully.");
        logToFile("generated/success.txt", "success");
    }
    catch (const std::string error) {
        debug("Data generation failed. " + error);
        logToFile("generated/err.txt", error);
    }

    // Exit will cause a crash but is good enough for what we need.
    exit(0);
    // The following will close gracefully but does not work if running servers as subprocesses.
    //HWND hwnd = GetConsoleWindow();
    //SendMessage(hwnd, WM_CLOSE, 0, 0);

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
