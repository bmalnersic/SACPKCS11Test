#ifndef PKCS11_BASICS_H_   /* Include guard */
#define PKCS11_BASICS_H_

#include <windows.h>
#include "cryptoki.h"
#include "pkcs11t.h"

int Initialize(CK_FUNCTION_LIST_PTR_PTR	ppFunctions,
				HMODULE						*phModule);

#endif // PKCS11_BASICS_H_