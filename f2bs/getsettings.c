#include "F2BS.h"

SETTINGS WINAPI GetSettings(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[])
{
	SETTINGS retVal;
	INT i;
	ULONG ulSpaces;
	UINT8 uSpaces;
	HRESULT hr;

	ZeroMemory(&retVal, sizeof(SETTINGS));
	retVal.uSpaces = 1;
	for (i = 1; i < nArgc; i++)
	{
		if (L'-' == pArgv[i][0] || L'/' == pArgv[i][0] && wcslen(pArgv[i]) >= 2U)
		{
			retVal.fHexSyntax = retVal.fHexSyntax || (towupper(pArgv[i][1]) == L'X');
			retVal.fCommaSep = retVal.fCommaSep || (towupper(pArgv[i][1]) == L'C');
			if (1 == retVal.uSpaces && towupper(pArgv[i][1]) == L'S')
			{
				INT nOff = 2 + (L':' == pArgv[i][2]);
				ulSpaces = wcstoul(&pArgv[i][nOff], NULL, 10);
				hr = ULongToUInt8(ulSpaces, &uSpaces);
				if (SUCCEEDED(hr))
				{
					retVal.uSpaces = uSpaces;
				}
			}
		}
		else if (L'\0' == retVal.wszFileName[0])
		{
			StringCchCopyW(retVal.wszFileName, MAX_PATH, pArgv[i]);
		}	
	}

	return retVal;
}