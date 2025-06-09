#include "include.h"

uintptr_t base = (uintptr_t)GetModuleHandleA("client.dll");
uintptr_t GetPawnFromHandle(uint32_t handle) // HANDLE - id in cs2 
{
    if (handle == -1) {
        return 0;
    }
    uintptr_t listEntry = *(uintptr_t*)(base + dwEntityList);
    if (!listEntry) {
        return 0;
    }
    uintptr_t pawn = *(uintptr_t*)(listEntry + 0x8 * ((handle & 0x7FFF) >> 9) + 0x10);
    if (!pawn) {
        std::cout << "pawn = nullptr" << std::endl;
    }
    pawn = *(uintptr_t*)(pawn + 0x78 * ((handle & 0x7FFF) & 0x1FF));
    return pawn;
}


BOOL WINAPI triggerThread(HMODULE hModule) 
{
   AllocConsole();
   FILE* Dummy;
   freopen_s(&Dummy, "CONOUT$", "w+", stdout);

   while (!GetAsyncKeyState(VK_END)) {
       uintptr_t localPlayerController = *(uintptr_t*)(base + offsets::client_dll::dwLocalPlayerController);
       if (!localPlayerController) continue;

       uintptr_t pawnHandle = *(uint32_t*)(localPlayerController + m_hPawn);
       uintptr_t localPawn = GetPawnFromHandle(pawnHandle);
       if (!localPawn) continue;

       int targedEntIndex = *(int*)(localPawn + offsets::C_CSPlayerPawnBase::m_iIDEntIndex);
       if (targedEntIndex == -1) continue;

       uintptr_t enemyPawn = GetPawnFromHandle(targedEntIndex);
       if (!enemyPawn) continue;

       int teamLocal = *(int*)(localPawn + m_iTeamNum);
       int teamEnemy = *(int*)(enemyPawn + m_iTeamNum);
        static ULONGLONG lastShotTime = 0;  
        ULONGLONG currenttime = GetTickCount64();  

        if (currenttime - lastShotTime > 100) {  
           lastShotTime = currenttime;  
           mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  
           Sleep(5);  
           mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  
        }
       std::cout << "teamLocal : " << teamLocal << std::endl;
       std::cout << "teamEnemy : " << teamEnemy << std::endl;

       if (teamLocal != teamEnemy) {
           std::cout << "ENEMY IN CROSSHAIR!" << std::endl;

           static DWORD lastShotTime = 0;
           DWORD currenttime = GetTickCount();

           if (currenttime - lastShotTime > 100) {
               lastShotTime = currenttime;
               mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
               Sleep(5);
               mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
           }
       }
       else {
           std::cout << "ENEMY NOT IN CROSSHAIR!" << std::endl;
       }

       Sleep(1); 
   }




   return TRUE; 
}

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                    )
{
   if (ul_reason_for_call == DLL_PROCESS_ATTACH)
   {
       DisableThreadLibraryCalls(hModule);
       CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)triggerThread, 0, 0, 0));
   }
   return TRUE;
}
