#include <Windows.h>
#include <iostream>



int main()
{

	//create file
	HANDLE file = CreateFileA(FILE_PATH "test.txt", GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//check if it worked
	if (file != INVALID_HANDLE_VALUE)
	{

		constexpr int size = 100;
		
		
		HANDLE fileMapping = CreateFileMappingA(file, NULL, PAGE_READWRITE, 
			0, size, NULL);

		//checking for failure again, this time we check if it is not NULL not INVALID_HANDLE_VALUE
		if (fileMapping == NULL)
		{
			//don't forget to close resources on fail
			CloseHandle(file);
		}
		else
		{

			//this gives us the actual mapping. Think of CreateFileMappingA as just 
			//preparing the os for this call.
			char *data = (char*)MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, size);

			if (data != nullptr)
			{

				//write data
				strcpy(data, "Hello world");


				while (!GetAsyncKeyState(VK_ESCAPE))
				{
					std::cout << data << "\n";
				}

				//final cleanup
				UnmapViewOfFile(data);		//MapViewOfFile
				CloseHandle(fileMapping);	//CreateFileMappingA
				CloseHandle(file);			//CreateFileA
				
			}
			else
			{
				//clear resources on fail.
				CloseHandle(fileMapping);
				CloseHandle(file);
			}
		}

	}

	
	return 0;
}
