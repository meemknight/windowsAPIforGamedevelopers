#include <Windows.h>
#include <iostream>

std::string getLastErrorAsString();

int main()
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO c = {};
	
	if (GetConsoleCursorInfo(0, &c)) //uops, forgot to pass stdHandle here
	{


		std::cout << "Good";
	}
	else
	{
		std::cout << "Error! " << getLastErrorAsString() << "\n";
	}


	std::cin.get();
	return 0;

}


std::string getLastErrorAsString()
{
	DWORD err = GetLastError();

	if (!err) { return ""; } //no wrror


	char *message = 0;

	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		0, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char *)&message, 0, nullptr);

	std::string rez(message, size); //copy the data into a string

	LocalFree(message); //FORMAT_MESSAGE_ALLOCATE_BUFFER allocates memory for us so we need to clear it.

	return rez;
}