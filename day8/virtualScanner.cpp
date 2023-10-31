#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>


DWORD findPidByName(const char *name)
{
	HANDLE h;
	PROCESSENTRY32 singleProcess;
	h = CreateToolhelp32Snapshot( //takes a snapshot of specified processes
		TH32CS_SNAPPROCESS, //get all processes
		0); //ignored for SNAPPROCESS

	singleProcess.dwSize = sizeof(PROCESSENTRY32);

	do
	{
		if (strcmp(singleProcess.szExeFile, name) == 0)
		{
			DWORD pid = singleProcess.th32ProcessID;
			CloseHandle(h);
			return pid;
		}

	} while (Process32Next(h, &singleProcess));

	CloseHandle(h);

	return 0;
}


void scanVirtualPages(HANDLE handleToProcess)
{
	//get the page size info
	SYSTEM_INFO sSysInfo = {};
	GetSystemInfo(&sSysInfo);


	//here we get back the memory information for that page or pages
	MEMORY_BASIC_INFORMATION memInfo;

	void *currentScanAddress = 0;

	while (true)
	{
		SIZE_T readBytes = 
			VirtualQueryEx(handleToProcess, currentScanAddress, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

		if (!readBytes)
		{
			return;
		}

		currentScanAddress = (char *)memInfo.BaseAddress + memInfo.RegionSize;

		//we want to only look at commited memory
		if (memInfo.State == MEM_COMMIT)
		{
			//this is a read write page, don't foget that there are other flags 
			//	like PAGE_EXECUTE_READWRITE or PAGE_READONLY
			
			if (memInfo.Protect == PAGE_READWRITE)
			{
				std::cout << "Found READWRITE page(s) at base address: " << memInfo.BaseAddress << " Size: "
					<< memInfo.RegionSize << " = pages count: " << memInfo.RegionSize / sSysInfo.dwPageSize << "\n";
			}

		}
	}
}

int main()
{

	auto pid = findPidByName("victim.exe");

	if (pid)
	{
		std::cout << "Found the victim process!\n";

		HANDLE handleToProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

		if (handleToProcess)
		{
			scanVirtualPages(handleToProcess);
		}
		else
		{
			std::cout << "Failed to open process.\n";
		}

	}
	else
	{
		std::cout << "couldn't find victim process :/\n";
	}

	std::cin.ignore();
	std::cin.get();
	return 0;
}
