#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char *data = "hello world";
	DWORD characters = 0; //characters written


	if(1)
	{
		//version 1

		WriteConsoleOutputCharacter(h, data, strlen(data), {}, &characters);
	}else
	{
		//version 2

		HANDLE consolebuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, 
			CONSOLE_TEXTMODE_BUFFER, 0);
		SetConsoleActiveScreenBuffer(consolebuffer);

		WriteConsoleOutputCharacter(h, data, strlen(data), {}, &characters);
	}

	
	std::cin.get();
	return 0;

}