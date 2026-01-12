#include <windows.h>
#include <d3d8.h>

typedef IDirect3D8* (WINAPI* Direct3DCreate8_t)(UINT);

static HMODULE real_d3d8 = NULL;
static Direct3DCreate8_t real_Direct3DCreate8 = NULL;

IDirect3D8* WINAPI Hook_Direct3DCreate8(UINT SDKVersion)
{
    // 调用真正的 Direct3DCreate8
    IDirect3D8* d3d8 = real_Direct3DCreate8(SDKVersion);

    // 这里是你真正“接管 DX”的起点
    if (d3d8)
    {
        MessageBoxA(NULL,
            "Direct3DCreate8 hooked successfully!",
            "DXDLL",
            MB_OK | MB_ICONINFORMATION);
    }

    return d3d8;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);

        char sysPath[MAX_PATH];
        GetSystemDirectoryA(sysPath, MAX_PATH);
        lstrcatA(sysPath, "\\d3d8.dll");

        real_d3d8 = LoadLibraryA(sysPath);
        if (!real_d3d8)
        {
            MessageBoxA(NULL, "Failed to load system d3d8.dll", "DXDLL", MB_ICONERROR);
            return FALSE;
        }

        real_Direct3DCreate8 =
            (Direct3DCreate8_t)GetProcAddress(real_d3d8, "Direct3DCreate8");

        if (!real_Direct3DCreate8)
        {
            MessageBoxA(NULL, "Failed to get Direct3DCreate8", "DXDLL", MB_ICONERROR);
            return FALSE;
        }
    }
    return TRUE;
}
