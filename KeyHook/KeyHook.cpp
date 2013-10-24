// KeyHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "KeyHook.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

KeyMappingInformation  *lpMapping;

HMODULE hInst = 0;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hInst = hModule;
		HANDLE hMapping;
		hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,true,_T("War3KeyMappingShared"));
		if (!hMapping)
			hMapping = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(KeyMappingInformation),_T("War3KeyMappingShared"));
		lpMapping = (KeyMappingInformation*)MapViewOfFile(hMapping,FILE_MAP_WRITE,0,0,0);
		if(!lpMapping) {
			MessageBox(0,_T("OpenFileMapping failed"),_T("Error"),0);
			return FALSE;
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

LRESULT CALLBACK KeyboardProc(    int code,
    WPARAM wParam,
    LPARAM lParam
	) 
{
	if (code>=0) 
		if (GetKeyState(VK_SCROLL)){
			EnterCriticalSection(&(lpMapping->CriticalSection));
			for(int i=0;i<lpMapping->nMappingCount;i++)
				if(lpMapping->OriginalKey[i]==wParam) {
					keybd_event(lpMapping->MappedKey[i],0,
						(lParam>>31==0)?0:KEYEVENTF_KEYUP,
						0);
					LeaveCriticalSection(&(lpMapping->CriticalSection));
					return 1;
				}
			LeaveCriticalSection(&(lpMapping->CriticalSection));
		}
	return CallNextHookEx(lpMapping->hHook,code,wParam,lParam);
}

KEYHOOK_API int Hook(DWORD dwThreadId)
{
	lpMapping->hHook = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,hInst,dwThreadId);
	return (int) lpMapping->hHook;
}

KEYHOOK_API int Unhook(void)
{
	BOOL rtn = UnhookWindowsHookEx(lpMapping->hHook);
	lpMapping->hHook = 0;
	return rtn;
}
