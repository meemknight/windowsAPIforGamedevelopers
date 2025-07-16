#include <gameLogic.h>
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>

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

	if (input.keyBoard[Button::P].pressed)
	{
		isOpenGLEnabled() = !isOpenGLEnabled();
	}


	//clear screen
	gameWindowBuffer.clear();


	//draw rectangle
	//for (int i = 0; i < 100; i++)
	//	for (int j = 0; j < 100; j++)
	//	{
	//		gameWindowBuffer.drawAtSafe(i, j, 0, 255, 255);
	//	}


	for (int i = 0; i < gameWindowBuffer.w; i++)
		for (int j = 0; j < gameWindowBuffer.h; j++)
		{
			gameWindowBuffer.drawAtSafe(i, j, i%256, j%256, (i*j)%256);
		}


	//opengl
	glClear(GL_COLOR_BUFFER_BIT);

	//basic triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex2f(0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex2f(0.0f, 0.5f);
	glEnd();




	return true;
}

void closeGameLogic()
{
}





