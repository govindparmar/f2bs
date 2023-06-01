#include "F2BS.h"

INT WINAPIV WMain(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[])
{
	CONST HANDLE hHeap = GetProcessHeap();
	LARGE_INTEGER liSize = { 0 };
	BYTE *bBuffer = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	SETTINGS settings;
	DWORD i = 0, dwError, dwRead = ULONG_MAX, dwToRead;
	HRESULT hr;
	SIZE_T cbAlloc;

	if (nArgc < 2)
	{
		_putws(L"Usage: F2BS [/x] [/c] inputfile\n\t/x\tUse 0x notation\n\t/c\tSeparate bytes with commas");
		return 0;
	}

	settings = GetSettings(nArgc, pArgv);
#ifdef _DEBUG
	wprintf_s(L"Read settings:\n\tHex syntax: %s\n\tComma separated: %s\n\tFile name: %s\n\n", BOOLTOSTRING(settings.fHexSyntax), BOOLTOSTRING(settings.fCommaSep), settings.wszFileName);
#endif
	hFile = CreateFileW(settings.wszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwError = GetLastError();
		fwprintf_s(stderr, L"Could not open %s: %I32u\n", settings.wszFileName, dwError);
		goto cleanup;
	}

	GetFileSizeEx(hFile, &liSize);
	cbAlloc = min(65536, (SIZE_T)liSize.QuadPart);
	bBuffer = (BYTE *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbAlloc);
	if (NULL == bBuffer)
	{
		dwError = ERROR_OUTOFMEMORY;
		fwprintf_s(stderr, L"File is empty or the system is out of memory.\n");
		goto cleanup;
	}

	while (liSize.QuadPart)
	{
		hr = ULongPtrToDWord(cbAlloc, &dwToRead);
		assert(SUCCEEDED(hr));
		if (ReadFile(hFile, bBuffer, dwToRead, &dwRead, NULL))
		{
			for (i = 0; i < dwRead; i++)
			{
				if (settings.fHexSyntax)
				{
					wprintf_s(L"0x");
				}
				wprintf_s(L"%.2hhX", bBuffer[i] & 0xFF);
				if (settings.fCommaSep && i != (dwRead - 1))
				{
					wprintf_s(L",");
				}
				else
				{
					wprintf_s(L" ");
				}
			}
		}
		else
		{
			dwError = GetLastError();
			if (dwError != ERROR_IO_PENDING)// Impossible with synchronous IO but for future 
			{
				fwprintf_s(stderr, L"Error reading file: %I32u\n", dwError);
				goto cleanup;
			}
		}

		liSize.QuadPart -= dwRead;
		cbAlloc = min(65536, (SIZE_T)liSize.QuadPart);
	}

cleanup:
	if (bBuffer != NULL)
	{
		HeapFree(hHeap, 0, bBuffer);
		bBuffer = NULL;
	}
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}

	return 0;
}