#pragma once
#define WIN32_LEAN_MEAN

#include <windows.h>
#include <stdexcept>
#include <tchar.h>
#include <d3dx9.h>
#include <vector>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SAFE_RELEASE(p) { if(p) { p->Release(); p = NULL; }}
#define SAFE_DELETE(p) { if(p) {delete p; p = NULL; }}