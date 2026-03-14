#pragma once
#include <input.h>
#include <gameWindowBuffer.h>


bool initGameplay();

bool gameplayFrame(float deltaTime, int w, int h, Input &input, 
	GameWindowBuffer &gameWindowBuffer);

void closeGameLogic();


void enableOpenGL();
void enablePixelDrawing();
bool &isOpenGLEnabled();
