#include <opengl.h>
#include <glad/gl.h>
#include <glad/wgl.h>

//link opengl if using visual studio
//#pragma comment(lib, "opengl32.lib")

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

#include <iostream>


HGLRC enableModernOpenGL(HWND hwnd)
{

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
	pfd.cAlphaBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;


	const int iPixelFormatAttribList[] = {

		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, //enable MSAA
		WGL_SAMPLES_ARB, 4,		   //enable MSAA
		0 // End of attributes list
	};

	int attributes[] = {
		//WGL_CONTEXT_MAJOR_VERSION_ARB, 3
		//, WGL_CONTEXT_MINOR_VERSION_ARB, 2
		//, WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	int nPixelFormat = 0;
	UINT iNumFormats = 0;

	//https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
	wglChoosePixelFormatARB(hDC, iPixelFormatAttribList, NULL, 1, &nPixelFormat, (UINT *)&iNumFormats);

	SetPixelFormat(hDC, nPixelFormat, &pfd);

	//https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
	HGLRC hRC = wglCreateContextAttribsARB(hDC, 0, attributes);

	wglMakeCurrent(hDC, hRC);

	if (!gladLoaderLoadGL())
	{
		std::cout << "Error loading GL\n";
	}

	ReleaseDC(hwnd, hDC);
	
	return hRC;
}

LRESULT CALLBACK tempWindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}


bool createFakeWindowAndLoadOpenGL()
{

	//---- fake Window
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = tempWindProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandleA(0);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "fakeWindowLmao";
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	HWND hwnd = CreateWindow(
		"fakeWindowLmao",
		"xddd",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		GetModuleHandleA(0),
		NULL
	);

	HDC hdc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd = {};

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(hdc, &pfd);

	SetPixelFormat(hdc, nPixelFormat, &pfd);

	HGLRC hrc = wglCreateContext(hdc);

	wglMakeCurrent(hdc, hrc);

	if (!gladLoaderLoadWGL(hdc))
	{
		std::cout << "Error loading WGL\n";
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);

	return true;
}

