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
	Sleep(32);
}

bool pointInRect(POINT p, RECT r, int padding)
{
	if (p.x > r.left - padding && p.x < r.right + padding
		&& p.y > r.top - padding && p.y < r.bottom + padding)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	createTheWindow();

	HWND wind = FindWindow(0, "title");
	std::cout << wind << "\n";


	POINT lastMousePos = {};
	GetCursorPos(&lastMousePos);

	while (true)
	{
		POINT p = {};
		GetCursorPos(&p);

		RECT r = {};
		GetWindowRect(wind, &r);

		POINT mouseDelta = {p.x - lastMousePos.x, p.y - lastMousePos.y};

		if (pointInRect(p, r, 50))
		{
			SetWindowPos(wind, 0, 
				r.left + mouseDelta.x*2, r.top + mouseDelta.y*2,
				0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		lastMousePos = p;
	}

	return 0;
}



