#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(h, &ci);	//get the old settings
	ci.bVisible = 0;				//changing them
	SetConsoleCursorInfo(h, &ci);	//applying the changes

	std::cout << "test";
	

	std::cin.get();
	return 0;

}


