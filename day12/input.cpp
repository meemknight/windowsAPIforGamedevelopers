#include <Windows.h>
#include <input.h>


void processInputAfter(Input &input)
{
	for (int i = 0; i < Button::BUTTONS_COUNT; i++)
	{
		input.keyBoard[i].pressed = 0;
		input.keyBoard[i].released = 0;
	}
}

void resetInput(Input &input)
{
	ZeroMemory(input.keyBoard, sizeof(input.keyBoard));
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

