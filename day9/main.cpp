#include <Windows.h>
#include <iostream>
#include <common.h>


int main()
{
	
	HMODULE dll = LoadLibraryA("dllProject.dll");

	if (dll)
	{
		//you can also do: decltype(foo) *fooPointer  = ...;
		foo_t *fooPointer = (foo_t *)GetProcAddress(dll, "foo");

		if (fooPointer)
		{
			fooPointer();
		}
		else
		{
			std::cout << "Error loading the function\n";
		}

		FreeLibrary(dll); //unload the DLL.
	}
	else
	{
		std::cout << "Error loading DLL\n";
	}

	std::cin.get();
	return 0;
}