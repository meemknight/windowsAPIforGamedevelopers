#include <Windows.h>
#include <iostream>

SYSTEM_INFO sSysInfo;

//rounds up the value to be multiple of page size
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
	//get the page size info
	GetSystemInfo(&sSysInfo);

	std::cout << "Page size: " << sSysInfo.dwPageSize << "\n";
	std::cout << "Round Up test: " << roundUP(5000) << "\n";

	void *memory = VirtualAlloc(0, 200,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (memory)
	{
		std::cout << memory << "\n";

		((unsigned char *)memory)[300] = 5;
		
		std::cout << (int)((unsigned char *)memory)[300] << "\n";

		//guarding the page example
		DWORD old = 0;
		VirtualProtect(memory, roundUP(200), PAGE_NOACCESS, &old);
		//this would crash the program if called
		//((unsigned char *)memory)[300] = 6;

		VirtualFree(memory, 0, MEM_RELEASE);
	}


	std::cin.get();

	return 0;
};


