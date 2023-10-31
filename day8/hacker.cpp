#include <Windows.h>
#include <TlHelp32.h> //for CreateToolhelp32Snapshot
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


int main()
{
	
	auto pid = findPidByName("victim.exe");

	if (pid)
	{
		std::cout << "Found the victim process!\n";

		HANDLE handleToProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

		if (handleToProcess)
		{
			std::cout << "Enter memory address:\n";
			void *address = 0;
			std::cin >> address;

			int data = 0;
			ReadProcessMemory(handleToProcess, address, &data, sizeof(data), nullptr);

			std::cout << data << "\n";

			int newData = 69;
			if (WriteProcessMemory(handleToProcess, address, &newData, sizeof(newData), nullptr))
			{
				std::cout << "Successfully written the data!\n";
			}

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





