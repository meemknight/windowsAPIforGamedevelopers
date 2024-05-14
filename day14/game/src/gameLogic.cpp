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


bool gameplayFrame(float deltaTime, int w, int h, Input &input)
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

	//std::cout << deltaTime << '\n';
	//std::cout << w << " " << h << '\n';

	//game code and other stuff
	//

	//if (input.keyBoard[Button::A].pressed
	//	&& input.keyBoard[Button::A].altWasDown)
	//{
	//	std::cout << "Pressed! + Alt\n";
	//}

	//if(input.lMouseButton.pressed)
	//{
	//	std::cout << "Pressed!\n";
	//}

	//std::cout << (int)input.keyBoard[Button::A].held << "\n";

	//std::cout << (int)input.focused << "\n";

	//std::cout << input.cursorX << " " << input.cursorY << "\n";

	//std::cout << input.typedInput;

	//if (input.keyBoard[Button::A].released)
	//{
	//	std::cout << "Released!\n";
	//}
	//

	return true;
}



void closeGameLogic()
{

}

