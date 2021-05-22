#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include "offsets.h"
#include "vector3.h"
#include "glow.h"
#include <vector>


float getDistance(uintptr_t pEntity, uintptr_t pLocalPlayer)
{
    vec3 myLoc = *(vec3*)(pLocalPlayer + netvars.m_vecOrigin);
    vec3 eLoc = *(vec3*)(pEntity + netvars.m_vecOrigin);

    return sqrt(pow(myLoc.x - eLoc.x, 2) + pow(myLoc.y - eLoc.y, 2) + pow(myLoc.z - eLoc.z, 2));
}

void setGlowColor(uintptr_t glowObject, int glowIndex)
{
    *(float*)(glowObject + (glowIndex * 0x38) + 0x4) = 2.0f;
    *(float*)(glowObject + (glowIndex * 0x38) + 0xC) = 2.0f;
    *(float*)(glowObject + (glowIndex * 0x38) + 0x10) = 2.0f;
    *(bool*)(glowObject + (glowIndex * 0x38) + 0x24) = true;
    *(bool*)(glowObject + (glowIndex * 0x38) + 0x25) = false;
    *(int*)(glowObject + (glowIndex * 0x38) + 0x2C) = 1;
}



DWORD WINAPI csgoDebugger(HMODULE hModule)
{
    //Creating console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "CSGO DEBUG TOOL, MADE BY SENKO\nPRESS ESCAPE TO UNINJECT\n" << std::endl;

    //settings
    bool crosshairDebug{ false };


    uintptr_t clientModule = (uintptr_t)GetModuleHandle(L"client.dll");
    uintptr_t engineModule = (uintptr_t)GetModuleHandle(L"engine.dll");
    uintptr_t localPlayer = *(uintptr_t*)(clientModule + 0x4DA720C);
    uintptr_t entList = 0x4DA71FC;
    
    
    while (true)
    {

        if(GetAsyncKeyState(VK_ESCAPE) & 1)
            break;

        if(GetAsyncKeyState(VK_F1) & 1)
        {
            crosshairDebug = !crosshairDebug;
            crosshairDebug ? std::cout << "CROSSHAIRDEBUG ON\n" : std::cout << "CROSSHAIRDEBUG OFF\n";
        }

        if (crosshairDebug) 
        {
            int crosshairID = *(int*)(localPlayer + netvars.m_iCrosshairId);

            if (crosshairID != 0 && crosshairID < 64)
            {
                uintptr_t entity = *(uintptr_t*)(clientModule + entList + crosshairID * 0x10);
                uintptr_t glowObject = *(uintptr_t*)(clientModule + signatures.dwGlowObjectManager);

                if (entity != NULL)
                {
                    int eTeam =     *(int*)(entity + netvars.m_iTeamNum);
                    int eHealth =   *(int*)(entity + netvars.m_iHealth);
                    int glowIndex = *(int*)(entity + netvars.m_iGlowIndex);
                    vec3 ePos =     *(vec3*)(entity + netvars.m_vecOrigin);
                    setGlowColor(glowObject, glowIndex);

                    system("cls");
                    std::cout
                        << std::setprecision(4)
                        << "LOCALPLAYER: "                              << std::hex             << std::dec
                        << "0x4DA720C"                                  << std::endl

                        << "ENT NUMBER " << crosshairID << " FOUND"     << std::endl            << std::hex
                        << "ENTITY ADDRESS: "                           << entity               << std::dec
                                                                                                << std::endl
                        << "======================================="    << std::endl
                        << "ENTITY m_iTeamNum: "                        << eTeam                << std::endl
                        << "ENTITY m_iHealth: "                         << eHealth              << std::endl
                        << "ENTITY m_iGlowIndex: "                      << glowIndex            << std::endl
                        << "ENTITY X: "                                 << ePos.x               << std::endl
                        << "ENTITY Y: "                                 << ePos.y               << std::endl
                        << "ENTITY Z: "                                 << ePos.z               << std::endl
                        << "DISTANCE INBETWEEN: "                       << getDistance(entity, localPlayer) << std::endl;
                }
            }
        }




        Sleep(1);
    }

    

    std::cout << "UNINJECTING..." << std::endl;
    _fcloseall();
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

    int GetClosestEnt()
    {
        uintptr_t clientModule = (uintptr_t)GetModuleHandle(L"client.dll");
        uintptr_t engineModule = (uintptr_t)GetModuleHandle(L"engine.dll");
        uintptr_t localPlayer = *(uintptr_t*)(clientModule + 0x4DA720C);
        uintptr_t entList = 0x4DA71FC;


    }




BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE hThread = nullptr;
        hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)csgoDebugger, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}