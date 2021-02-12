#include "F2BS.h"

SETTINGS WINAPI GetSettings(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[])
{
	SETTINGS retVal;
	INT i;

	ZeroMemory(&retVal, sizeof(SETTINGS));

	for (i = 0; i < nArgc; i++)
	{
		if (L'-' == pArgv[i][0] || L'/' == pArgv[i][0] && wcslen(pArgv[i]) >= 2U)
		{
			retVal.fHexSyntax = retVal.fHexSyntax || (towupper(pArgv[i][1]) == L'X');
			retVal.fCommaSep = retVal.fCommaSep || (towupper(pArgv[i][1]) == L'C');
		}
		else if (L'\0' == retVal.wszFileName[0])
		{
			StringCchCopyW(retVal.wszFileName, MAX_PATH, pArgv[i]);
		}	
	}

	return retVal;
}