#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

struct Test
{
	float a = 0;
	int b = 0;
};


size_t getFileSize(std::string name);
bool readEntireFileBinary(std::string name, std::vector<unsigned char> &data);
bool writeEntireFileBinary(std::string_view name, void *buffer, size_t s);

int main()
{
	
	Test t;
	t.a = 10.8;
	t.b = 5;

	//FILE_PATH macro is defined from cmake and it is an absolute path, used for convinience
	writeEntireFileBinary(FILE_PATH "test.bin", &t, sizeof(t));

	t = {};

	std::vector<unsigned char> data;
	readEntireFileBinary(FILE_PATH "test.bin", data);
	
	if(sizeof(t) == data.size())
		std::memcpy(&t, data.data(), sizeof(t));
	
	std::cout << t.a << " " << t.b << "  file size bytes: " << getFileSize(FILE_PATH "test.bin");
	std::cin.get();
	return 0;
}	


size_t getFileSize(std::string name)
{
	HANDLE file = CreateFile(name.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		// log error here
		return 0;
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(file, &fileSize))
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);
	return fileSize.QuadPart;
}

bool readEntireFileBinary(std::string name, std::vector<unsigned char> &data)
{

	data.clear();

	HANDLE file = CreateFile(name.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		// log error here
		return false;
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(file, &fileSize))
	{
		CloseHandle(file);
		return 0;
	}

	data.resize(fileSize.QuadPart);
	
	DWORD bytesRead = 0;
	bool rez = ReadFile(file, data.data(), fileSize.QuadPart, &bytesRead, nullptr);

	CloseHandle(file);

	if (!rez || bytesRead == fileSize.QuadPart)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

bool writeEntireFileBinary(std::string_view name, void *buffer, size_t s)
{
	HANDLE file = CreateFile(name.data(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		// log error here
		return false;
	}

	if (!buffer || s == 0)
	{
		CloseHandle(file);
		return true;
	}

	DWORD bytesWritten;
	bool success = WriteFile(file, buffer, static_cast<DWORD>(s), &bytesWritten, NULL) && bytesWritten == s;
	CloseHandle(file);
	return success;
}