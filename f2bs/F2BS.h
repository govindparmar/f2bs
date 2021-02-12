#pragma once
#include <Windows.h>
#include <strsafe.h>
#include <sal.h>

#define BOOLTOSTRING(b) ((b) ? L"True" : L"False")
#define WMain wmain

typedef struct _SETTINGS
{
	BOOL fHexSyntax;
	BOOL fCommaSep;
	WCHAR wszFileName[MAX_PATH];
} SETTINGS, *PSETTINGS;

SETTINGS WINAPI GetSettings(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[]);
INT WINAPIV WMain(_In_ INT nArgc, _In_reads_(nArgc) WCHAR *pArgv[]);
