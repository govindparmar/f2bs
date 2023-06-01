#include "F2BS.h"

SETTINGS WINAPI GetSettings(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[])
{
	SETTINGS retVal;
	INT i;
	LONG lSpaces;
	INT8 nSpaces;
	HRESULT hr;

	ZeroMemory(&retVal, sizeof(SETTINGS));
	retVal.nSpaces = 1;
	for (i = 1; i < nArgc; i++)
	{
		if (L'-' == pArgv[i][0] || L'/' == pArgv[i][0] && wcslen(pArgv[i]) >= 2U)
		{
			retVal.fHexSyntax = retVal.fHexSyntax || (towupper(pArgv[i][1]) == L'X');
			retVal.fCommaSep = retVal.fCommaSep || (towupper(pArgv[i][1]) == L'C');
			if (1 == retVal.nSpaces && towupper(pArgv[i][1]) == L'S')
			{
				INT nOff = 2 + (L':' == pArgv[i][2]);
				lSpaces = wcstoul(&pArgv[i][nOff], NULL, 10);
				hr = LongToInt8(lSpaces, &nSpaces);
				if (SUCCEEDED(hr))
				{
					retVal.nSpaces = nSpaces;
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