#pragma once
#include <Windows.h>


struct GameWindowBuffer
{
	char *memory = 0;
	int w = 0;
	int h = 0;

	void drawAtSafe(int x, int y, char r, char g, char b)
	{
		if (x >= w || y >= h || x < 0 || y < 0)
		{
			return;
		}

		memory[4 * (x + y * w) + 0] = b; //blue
		memory[4 * (x + y * w) + 1] = g; //green
		memory[4 * (x + y * w) + 2] = r; //red
		memory[4 * (x + y * w) + 3] = 0; //reserved for alignment
	}

	void clear(char r = 0, char g = 0, char b = 0)
	{
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++)
			{
				memory[4 * (x + y * w) + 0] = b; //blue
				memory[4 * (x + y * w) + 1] = g; //green
				memory[4 * (x + y * w) + 2] = r; //red
				memory[4 * (x + y * w) + 3] = 0; //reserved for alignment

			}
	}
};


void resetWindowBuffer(GameWindowBuffer *gameWindowBuffer, BITMAPINFO *bitmapInfo, HWND wind);