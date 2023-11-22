#include <iostream>
#include <thread>
#include <Windows.h>




void threadFunction()
{
	MessageBox(0, "content", "title", MB_OK);

	exit(0);
}

void createTheWindow()
{
	std::thread t(threadFunction);
	t.detach();
	Sleep(32); //wait some time for the thread and the window to open.
}


int main()
{

	createTheWindow();

	HWND wind = FindWindow(0, "title");
	std::cout << wind << "\n";


	while (true)
	{
		//show window
		if (GetAsyncKeyState('A') & 1) //if a was pressed...
		{
			std::cout << "Pressed A\n";
			ShowWindow(wind, SW_SHOW);
		}

		//hide window
		if (GetAsyncKeyState('S') & 1)
		{
			std::cout << "Pressed S\n";
			ShowWindow(wind, SW_HIDE);
		}

		//change window border
		if (GetAsyncKeyState('Q') & 1)
		{
			std::cout << "Pressed Q\n";
			auto style = GetWindowLongPtrA(wind, GWL_STYLE);
			style ^= WS_BORDER;
			SetWindowLongPtrA(wind, GWL_STYLE, style);
		}

		//diasble window
		if (GetAsyncKeyState('W') & 1)
		{
			std::cout << "Pressed W\n";
			auto style = GetWindowLongPtrA(wind, GWL_STYLE);
			style ^= WS_DISABLED;
			SetWindowLongPtrA(wind, GWL_STYLE, style);
		}

		//get window size
		if (GetAsyncKeyState('E') & 1)
		{
			std::cout << "Pressed E\n";

			RECT r = {};
			GetWindowRect(wind, &r);

			std::cout << "Window width: " << r.right - r.left << 
				" widnow height: " << r.bottom - r.top << '\n';
		}

		//set window pos
		if (GetAsyncKeyState('R') & 1)
		{
			std::cout << "Pressed R\n";
			
			SetWindowPos(wind, 0, 100, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		//set window size
		if (GetAsyncKeyState('T') & 1)
		{
			std::cout << "Pressed T\n";

			SetWindowPos(wind, 0, 0, 0, 300, 300, SWP_NOMOVE | SWP_NOZORDER);
		}

		//set window on top
		if (GetAsyncKeyState('Y') & 1)
		{
			std::cout << "Pressed Y\n";
			SetWindowPos(wind, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		//set window as topmost
		if (GetAsyncKeyState('U') & 1)
		{
			std::cout << "Pressed U\n";
			SetWindowPos(wind, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

	}

	return 0;
}



