#include <Windows.h>
#include <iostream>

SYSTEM_INFO sSysInfo;

size_t roundUP(size_t in)
{
	if (in == 0) { return 0; }

	if (in <= sSysInfo.dwPageSize)
	{
		return sSysInfo.dwPageSize;
	}
	else
	{
		size_t reminder = in % sSysInfo.dwPageSize;

		return in + (sSysInfo.dwPageSize - reminder);
	}
}

int main()
{
	GetSystemInfo(&sSysInfo);

	std::cout << "Page size: " << sSysInfo.dwPageSize << "\n";
	std::cout << "Round Up test: " << roundUP(5000) << "\n";

	void *memory = VirtualAlloc((void*)0xffff0001, 200, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (memory)
	{
		std::cout << memory << "\n";

		((unsigned char *)memory)[300] = 5;

		
		std:: cout << (int)((unsigned char *)memory)[300] << "\n";


		//guarding the page
		DWORD old = 0;
		VirtualProtect(memory, roundUP(200), PAGE_NOACCESS, &old);
		
		//this will crash the program
		//((unsigned char *)memory)[300] = 6;

		VirtualFree(memory, 0, MEM_RELEASE);
	}


	std::cin.get();
	
	return 0;
}
