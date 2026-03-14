#include <gameWindowBuffer.h>


void resetWindowBuffer(GameWindowBuffer *gameWindowBuffer, BITMAPINFO *bitmapInfo, HWND wind)
{
	RECT rect = {};
	GetClientRect(wind, &rect);
	gameWindowBuffer->h = rect.bottom;
	gameWindowBuffer->w = rect.right;

	if (gameWindowBuffer->memory)
	{
		VirtualFree(gameWindowBuffer->memory, 0, MEM_RELEASE);
	}

	gameWindowBuffer->memory =
		(unsigned char *)VirtualAlloc(0, 4 * gameWindowBuffer->w * gameWindowBuffer->h,
		MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
	bitmapInfo->bmiHeader.biWidth = gameWindowBuffer->w;
	bitmapInfo->bmiHeader.biHeight = -gameWindowBuffer->h;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biBitCount = 32;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;
}


