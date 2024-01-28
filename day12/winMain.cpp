#include <iostream>
#include <Windows.h>
#include <input.h>

struct WindowStuff
{
	bool running = true;
	Input input;
};

WindowStuff windowStuff;

//this is the function that will process all of the windows' messages.
LRESULT windProc(HWND wind, UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT rez = 0;

	bool pressed = 0;

	switch (msg)
	{
		//if the window is closed we want to handle that case and signal that to our program
	case WM_CLOSE:
		windowStuff.running = false;
	break;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	pressed = 1;
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		

		for (int i = 0; i < Button::BUTTONS_COUNT; i++)
		{
			if (wp == Button::buttonValues[i])
			{
				processEventButton(windowStuff.input.keyBoard[i], pressed);
			}
		}

		//so altf4 works
		rez = DefWindowProc(wind, msg, wp, lp);

	}break;


	case WM_SETFOCUS:
		windowStuff.input.focused = true;
	break;

	case WM_KILLFOCUS:
		windowStuff.input.focused = false;
	break;


	default:
		//there are many messages that we didn't treat so we want to call the default window callback for those...
		rez = DefWindowProc(wind, msg, wp, lp);
	break;
	}

	return rez;
}


int main()
{

	WNDCLASS wc = {sizeof(WNDCLASS)};

	wc.hCursor = LoadCursor(0, IDC_ARROW);	//so we have a cursor for our window
	wc.hInstance = GetModuleHandle(0);		//program instance
	wc.lpszClassName = "EpicWindowClass";
	wc.style = CS_HREDRAW | CS_VREDRAW;		//refresh window on resize
	wc.lpfnWndProc = windProc;				//pass our callback function

	if (!RegisterClass(&wc)) { return 0; };


	HWND wind = CreateWindowA(
		wc.lpszClassName,
		"We have a Window!",				//window title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//default window
		CW_USEDEFAULT,						//position x
		CW_USEDEFAULT,						//position y
		CW_USEDEFAULT,						//size x
		CW_USEDEFAULT,						//size y
		0, 0, GetModuleHandle(0), 0			//other uninteresting stuff
	);

	while (windowStuff.running)
	{

		MSG msg = {};
		while (PeekMessage(&msg, wind, 0, 0, PM_REMOVE) > 0) //remove all mesages from queue
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); //call our window callback
		
		}
		
		if (!windowStuff.input.focused)
		{
			resetInput(windowStuff.input);
		}
		
		//game code and other stuff
		//

		if (windowStuff.input.keyBoard[Button::A].pressed)
		{
			std::cout << "Pressed!\n";
		}

		//std::cout << (int)windowStuff.input.keyBoard[Button::A].held << "\n";

		//std::cout << (int)windowStuff.input.focused << "\n";

		if (windowStuff.input.keyBoard[Button::A].released)
		{
			std::cout << "Released!\n";
		}
		//


		processInputAfter(windowStuff.input);

	}



	return 0;
}
