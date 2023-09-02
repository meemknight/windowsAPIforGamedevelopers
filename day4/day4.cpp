#include <Windows.h>
#include <string>

int main()
{
	
	
	OPENFILENAMEA f = {sizeof(OPENFILENAMEA)};

	f.lpstrFilter = "png files\0*.png\0jpg files\0*.jpg\0";

	f.lpstrTitle = "Dialog box lmao";

	char buff[MAX_PATH] = {};
	f.nMaxFile = sizeof(buff);
	f.lpstrFile = buff;

	GetOpenFileNameA(&f);

	return 0;
}	
