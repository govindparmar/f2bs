#pragma once
#include <Windows.h>
#include <intsafe.h>
#include <assert.h>
#include <strsafe.h>
#include <sal.h>

#ifdef _DEBUG
#define BOOLTOSTRING(b) ((b) ? L"True" : L"False")
#endif
#define WMain wmain

typedef struct _SETTINGS
{
	BOOL fHexSyntax;
	BOOL fCommaSep;
	WCHAR wszFileName[MAX_PATH];
} SETTINGS, *PSETTINGS;

SETTINGS WINAPI GetSettings(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[]);
INT WINAPIV WMain(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[]);
