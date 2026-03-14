#pragma once
#include <Windows.h>

HGLRC enableOpenGL(HWND hwnd);

HGLRC enableModernOpenGL(HWND hwnd);

bool createFakeWindowAndLoadOpenGL();