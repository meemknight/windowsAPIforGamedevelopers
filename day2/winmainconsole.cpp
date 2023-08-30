#include <Windows.h>
#include <fstream>
#include <iostream>

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{

	if (true)
	{
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		std::cout.sync_with_stdio();
	};


	std::cin.get();
	std::cout << "Yo, You you should totally like my videos " << (char)1 << " !";
	
	std::cin.get();
	std::cin.ignore();


	return 0;
}

