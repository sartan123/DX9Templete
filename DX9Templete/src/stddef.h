#pragma once
#define WIN32_LEAN_MEAN

#include <windows.h>
#include <tchar.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

template<class T>
void SafeRelease(T p) {
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

static std::wstring GetExecutionDirectory()
{
	wchar_t filePath[MAX_PATH];
	GetModuleFileNameW(NULL, filePath, sizeof(filePath));
	wchar_t* p = wcsrchr(filePath, L'\\');
	std::wstring strPath(filePath, p);
	return strPath;
}

static std::string GetStringExecutionDirectory()
{
	wchar_t filePath[MAX_PATH];
	GetModuleFileNameW(NULL, filePath, sizeof(filePath));
	wchar_t* p = wcsrchr(filePath, L'\\');
	std::string strPath(filePath, p);
	return strPath;
}