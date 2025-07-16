#include <opengl.h>

HGLRC enableOpenGL(HWND hwnd)
{


	// get the device context (DC)
	//Purpose: Represents a drawing surface, like a window or a printer.
	// It links GDI or OpenGL with the actual output device (monitor in this case).
	HDC hDC = GetDC(hwnd);

	
	PIXELFORMATDESCRIPTOR pfd = {};

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int iFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, iFormat, &pfd);

	// create and enable the render context (RC)
	HGLRC hRC = wglCreateContext(hDC);

	wglMakeCurrent(hDC, hRC);

	ReleaseDC(hwnd, hDC);

	return hRC;
}