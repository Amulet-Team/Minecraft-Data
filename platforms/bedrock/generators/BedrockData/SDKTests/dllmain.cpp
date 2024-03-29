#pragma once
#pragma comment(lib, "LLPreLoader.lib")
#pragma comment(lib, "SDK.lib")
#include <Windows.h>
#include <iostream>

#include "logging.hpp"
#include "tests/tests.hpp"


DWORD WINAPI MainThread(HMODULE hModule) {
    // print to the console that the DLL is running
    debug("SDKTests.dll Injected.");

    try {
        Test::main();
        debug("Passed all tests");
        logToFile("generated/pass.txt", "Passed all tests");
    }
    catch (const char* error) {
        debug(error);
        logToFile("generated/fail.txt", error);
    }

    // print to the console that we are done
    debug("Tests finished.");

    exit(0);

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
