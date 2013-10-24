// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KEYHOOK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KEYHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef KEYHOOK_EXPORTS
#define KEYHOOK_API __declspec(dllexport)
#else
#define KEYHOOK_API __declspec(dllimport)
#endif

// This class is exported from the KeyHook.dll
class KEYHOOK_API CKeyHook {
public:
	CKeyHook(void);
	// TODO: add your methods here.
};

extern KEYHOOK_API int nKeyHook;

KEYHOOK_API int fnKeyHook(void);

struct KeyMappingInformation {
	 CRITICAL_SECTION CriticalSection;
	 unsigned __int8 OriginalKey[255],MappedKey[255];
	 int nMappingCount;
	 HHOOK hHook;
};