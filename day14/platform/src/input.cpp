#include <Windows.h>
#include <input.h>


void processInputAfter(Input &input)
{
	for (int i = 0; i < Button::BUTTONS_COUNT; i++)
	{
		input.keyBoard[i].pressed = 0;
		input.keyBoard[i].released = 0;
		input.keyBoard[i].altWasDown = 0;
	}

	input.lMouseButton.pressed = 0;
	input.lMouseButton.released = 0;
	input.lMouseButton.altWasDown = 0;

	input.rMouseButton.pressed = 0;
	input.rMouseButton.released = 0;
	input.rMouseButton.altWasDown = 0;


	ZeroMemory(input.typedInput, sizeof(input.typedInput));
}

void resetInput(Input &input)
{
	input.lMouseButton = {};
	input.rMouseButton = {};

	ZeroMemory(input.keyBoard, sizeof(input.keyBoard));
	ZeroMemory(input.typedInput, sizeof(input.typedInput));
}

//newState == 1 means pressed else released
void processEventButton(Button &b, bool newState)
{
	if (newState)
	{
		if (!b.held)
		{
			b.pressed = true;
			b.held = true;
			b.released = false;
		}
	}
	else
	{
		b.pressed = false;
		b.held = false;
		b.released = true;
	}
}

