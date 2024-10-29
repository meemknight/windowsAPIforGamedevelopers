#include <gameLogic.h>
#include <iostream>
#include <Windows.h>

struct GameData 
{
	int positionX = 0;
	int positionY = 0;
	int fpsCounter = 0;
	float timer = 0;
};
static GameData data;

bool initGameplay()
{
	data = {};
	return true;
}

bool gameplayFrame(float deltaTime, 
	int w, int h, Input &input, GameWindowBuffer &gameWindowBuffer)
{

	//fps counter
	//Sleep(1);
	data.fpsCounter += 1;
	data.timer += deltaTime;
	if (data.timer > 1)
	{
		data.timer -= 1;
		std::cout << "FPS: " << data.fpsCounter << '\n';
		data.fpsCounter = 0;
	}

	//clear screen
	gameWindowBuffer.clear();


	//draw rectangle
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{
			gameWindowBuffer.drawAtSafe(i, j, 0, 255, 255);
		}


	for (int i = 0; i < gameWindowBuffer.w; i++)
		for (int j = 0; j < gameWindowBuffer.h; j++)
		{
			gameWindowBuffer.drawAtSafe(i, j, i%256, j%256, (i*j)%256);
		}



	return true;
}

void closeGameLogic()
{
}





