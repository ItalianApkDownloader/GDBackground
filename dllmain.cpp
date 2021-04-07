// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "extern/gd.h"
#include "hooks.h"

DWORD WINAPI my_thread(void* hModule) {
    //Your code goes here
    //====================
    if (!GD::init()) {
        MessageBox(0, L"ERROR!", L"Failed to obtain internal base address!", MB_OK | MB_ICONERROR);
        return -1;
    }

    //i was gonna use this but u can't hook the beginning of MenuLayer::init to add buttons lol
    if (MH_Initialize() != MH_OK) [[unlikely]] {
        MessageBox(0, L"ERROR!", L"Failed to initialize MinHook!", MB_OK | MB_ICONERROR);
        return -1;
    }

    //use this to add hooks, doesn't work for MenuLayer::init so i'm commenting this out
    if (MH_CreateHook(
        GD::MenuLayer::init,
        hooks::MenuLayer::init,
        reinterpret_cast<LPVOID*>(&gates::MenuLayer::init)) != MH_OK)
        [[unlikely]] {
        MessageBox(0, L"ERROR!", L"Failed to create hook!", MB_OK | MB_ICONERROR);
        MH_Uninitialize();
        return -1;
    }

    if (MH_EnableHook(GD::MenuLayer::init) != MH_OK) [[unlikely]] {
        MessageBox(0, L"ERROR!", L"Failed to enable hook!", MB_OK | MB_ICONERROR);
        MH_Uninitialize();
        return -1;
    }

    #if 0
    if (!hooks::detour(reinterpret_cast<char*>(GD::MenuLayer::init) + 0x420, hooks::MenuLayer::init, 5)) [[unlikely]] {
        MessageBox(0, L"ERROR!", L"Failed to setup hook!", MB_OK | MB_ICONERROR);
        return -1;
    }
    #endif

    //This line will dettach your DLL when executed. Remove if needed
    //FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

