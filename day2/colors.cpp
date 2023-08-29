#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(stdHandle, 0x0C);
	std::cout << "This is an error message\n";

	SetConsoleTextAttribute(stdHandle, 0x0f);
	std::cout << "Back to normal\n";

	//no need to call CloseHandle for GetStdHandle;

	std::cin.get();
	return 0;

}