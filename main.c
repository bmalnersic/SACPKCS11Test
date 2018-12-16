#include <stdio.h>
#include "pkcs11_basics.h" 

int main(int argc, char *argv[])
{
	printf("Test SAC PKCS#11 Library\n");
	CK_FUNCTION_LIST_PTR pFunctions = NULL;
	HMODULE hModule = NULL;

	printf("Initialize - load PKCS#11 module\n");
	// initialize
	Initialize(&pFunctions, &hModule);

	// finalize
	if (pFunctions != NULL) pFunctions->C_Finalize(NULL);
	if (hModule != NULL) FreeLibrary(hModule);

	return 0;
}