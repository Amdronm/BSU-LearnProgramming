// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the CRYPTODLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// CRYPTODLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CRYPTODLL_EXPORTS
#define CRYPTODLL_API __declspec(dllexport)
#else
#define CRYPTODLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class CRYPTODLL_API CCryptoDLL {
public:
	CCryptoDLL(void);
	// TODO: add your methods here.
};

extern CRYPTODLL_API int nCryptoDLL;

extern "C" CRYPTODLL_API void encrypt(char*, const char);

extern "C" CRYPTODLL_API void decrypt(char*, const char);
