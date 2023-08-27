#include <iostream>
#include <Windows.h>

int main()
{
	int code = MessageBox(0, "content", "title", MB_OKCANCEL);

	if (code == IDOK)
	{
		std::cout << "ok";
	}
	else if (code == IDCANCEL)
	{
		std::cout << "cancel";
	}

	std::cin.get();
	return 0;
}
