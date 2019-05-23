#pragma once
#define WIN32_LEAN_MEAN

#include <windows.h>
#include <tchar.h>
#include <stdexcept>
#include <vector>
#include <iostream>
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