// Based on Utimaco's PKCS11_HandsOn.pdf
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "pkcs11_basics.h"

int Initialize(CK_FUNCTION_LIST_PTR_PTR	ppFunctions,
				HMODULE						*phModule)
{
	// find a solution for loading dlls that are NOT in the Dll Search Path... (otherwise dll must be copied to Dll Search Path...)
	//char szDllName[]						= "C:\\Program Files(x86)\\Gemalto\\IDGo 800 PKCS#11\\IDPrimePKCS11.dll";
	LPCSTR szDllName = "C:\\Program Files(x86)\\Gemalto\\IDGo 800 PKCS#11\\IDPrimePKCS11.dll";

	// char szDllName[]						= "IDPrimePKCS11.dll";
	char *szDllPath						= "C:\\Program Files(x86)\\Gemalto\\IDGo 800 PKCS#11";
	CK_C_GetFunctionList pC_GetFunctionList = NULL;
	
	wchar_t wsDllPath[MAX_PATH];
	mbstowcs(wsDllPath, szDllPath, MAX_PATH);

	// load PKCS#11 library (use LoadLibraryA() to load ansi string (char))
	SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
	// SetDllDirectoryA(szDllPath);
	AddDllDirectory(wsDllPath);
	printf("Loading module: %s\n", szDllName);
	//(*phModule) = LoadLibraryA(szDllName);
	// https://docs.microsoft.com/en-us/windows/desktop/api/libloaderapi/nf-libloaderapi-loadlibraryexa
	// https://chromium.googlesource.com/chromium/src/base/+/master/native_library_win.cc
	// https://gist.github.com/rossy/5856556
	// http://www.flounder.com/loadlibrary_explorer.htm
	if (((*phModule) = LoadLibraryExA(szDllName, NULL, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_DEFAULT_DIRS)) != NULL)
	//if (((*phModule) = LoadLibraryA(szDllName)) != NULL)
	{
		printf("Loading module SUCCESSFUL\n");
	}
	else
	{
		printf("Loading module FAILED\n");
		return FALSE;
	}
	

	// get the address of the C_GetFunctionList function
	pC_GetFunctionList = (CK_C_GetFunctionList)GetProcAddress(
							(*phModule), "C_GetFunctionList");
	
	// get addresses of all the remaining PKCS#11 functions
	pC_GetFunctionList(ppFunctions);
	
	// initialize token
	(*ppFunctions)->C_Initialize(NULL);
}
