#include <iostream>
#include <Windows.h>
#include <input.h>
#include <gameLogic.h>
#include <chrono>

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

	case WM_LBUTTONDOWN:
		processEventButton(windowStuff.input.lMouseButton, true);
	break;

	case WM_LBUTTONUP:
		processEventButton(windowStuff.input.lMouseButton, false);
	break;

	case WM_RBUTTONDOWN:
	processEventButton(windowStuff.input.rMouseButton, true);
	break;

	case WM_RBUTTONUP:
	processEventButton(windowStuff.input.rMouseButton, false);
	break;


	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	pressed = 1;
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		bool altWasDown = lp & (1 << 29);

		for (int i = 0; i < Button::BUTTONS_COUNT; i++)
		{
			if (wp == Button::buttonValues[i])
			{
				processEventButton(windowStuff.input.keyBoard[i], pressed);
				windowStuff.input.keyBoard[i].altWasDown = altWasDown;
			}
		}

		if (pressed)
		{
			for (int i = 0; i < sizeof(windowStuff.input.typedInput) - 1; i++)
			{
				if (windowStuff.input.typedInput[i] == 0)
				{
					windowStuff.input.typedInput[i] = wp;
					break;
				}
			}
		};

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

#pragma region create window stuff

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

#pragma endregion

	if (initGameplay()) { return 1; };

	auto stop = std::chrono::high_resolution_clock::now();

	while (windowStuff.running)
	{

	#pragma region deltaTime

		auto start = std::chrono::high_resolution_clock::now();

		float deltaTime = (std::chrono::duration_cast<std::chrono::microseconds>(start - stop)).count() / 1000000.0f;
		stop = std::chrono::high_resolution_clock::now();

		//we don't want delta time to drop too low, like let's say under 5 fps. you can set this to whatever you want
		//or remove it but I recomand keeping it
		float augmentedDeltaTime = deltaTime;
		if (augmentedDeltaTime > 1.f / 5) { augmentedDeltaTime = 1.f / 5; }

	#pragma endregion

	#pragma region get messages
		MSG msg = {};
		while (PeekMessage(&msg, wind, 0, 0, PM_REMOVE) > 0) //remove all mesages from queue
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); //call our window callback

		}
	#pragma endregion

	#pragma region other input stuff
		{
			if (!windowStuff.input.focused)
			{
				resetInput(windowStuff.input);
			}

			POINT point;
			GetCursorPos(&point);
			ScreenToClient(wind, &point);
			windowStuff.input.cursorX = point.x;
			windowStuff.input.cursorY = point.y;
		}
	#pragma endregion

	#pragma region typed input

		//typed input
		{
			bool shiftWasPressed = windowStuff.input.keyBoard[Button::Shift].held;

			//Caps Lock is on
			if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
			{
				shiftWasPressed = !shiftWasPressed;
			}

			for (int i = 0; i < sizeof(windowStuff.input.typedInput) - 1; i++)
			{
				char &c = windowStuff.input.typedInput[i];
				if (c == 0) { break; }

				if (c > 0 && std::isalpha(c))
				{
					if (shiftWasPressed)
					{
						c = std::toupper(c);
					}
					else
					{
						c = std::tolower(c);
					}
				}
				else if (c > 0 && std::isdigit(c))
				{

				}
				else
				{
					char codes[] = {VK_SPACE, VK_RETURN, VK_BACK,
								VK_OEM_PLUS, VK_OEM_PERIOD, VK_OEM_MINUS,
							VK_OEM_COMMA, VK_OEM_1, VK_OEM_2, VK_OEM_3,
								VK_OEM_7, VK_OEM_5, VK_OEM_4, VK_OEM_6};

					char chars[] = {' ', '\n', '\b', '+', '.', '-', ',', ';', '/', '`',
						'\'', '\\', '[', ']'};

					static_assert(sizeof(codes) == sizeof(chars));

					bool found = false;
					for (int j = 0; j < sizeof(chars); j++)
					{
						if (c == codes[j])
						{
							c = chars[j];
							found = true;
						}
					}

					if (!found)
					{
						//remove this character completely from the array
						for (int j = i; i < sizeof(windowStuff.input.typedInput) - 1; i++)
						{
							windowStuff.input.typedInput[j] = windowStuff.input.typedInput[j + 1];
						}
					}

				}

			}

		}

	#pragma endregion

		RECT rect = {};
		GetWindowRect(wind, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		//todo deltaTime
		if (!gameplayFrame(augmentedDeltaTime, width, height, windowStuff.input))
		{
			windowStuff.running = false;
		}

		processInputAfter(windowStuff.input);
	}

	closeGameLogic();


	return 0;
}
