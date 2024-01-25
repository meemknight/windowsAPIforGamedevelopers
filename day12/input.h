#pragma once
#include <windows.h>


struct Button
{
	
	unsigned char pressed = 0;	//one in the first frame it is pressed
	unsigned char held = 0;		//one while is pressed
	unsigned char released = 0;	//one while is released

	enum
	{
		A = 0,
		B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NR0, NR1, NR2, NR3, NR4, NR5, NR6, NR7, NR8, NR9,
		Space,
		Enter,
		Escape,
		Up,
		Down,
		Left,
		Right,
		Shift,
		BackSpace, //next line 
		Plus_Equal,
		Period_RightArrow,
		Minus_Underscore,
		Comma_LeftArrow,
		SemiColon,
		Question_BackSlash,
		Tilde, //next line
		Quotes,
		Slash,
		SquareBracketsOpen,
		SquareBracketsClose,
		BUTTONS_COUNT, //
	};

	//todo add mouse buttons here todo also add alt was pressed function
	static constexpr int buttonValues[BUTTONS_COUNT] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		VK_SPACE, VK_RETURN, VK_ESCAPE, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SHIFT,
		VK_BACK, VK_OEM_PLUS, VK_OEM_PERIOD, VK_OEM_MINUS, VK_OEM_COMMA, VK_OEM_1, VK_OEM_2, VK_OEM_3,
		VK_OEM_7, VK_OEM_5, VK_OEM_4, VK_OEM_6,
	};


};



struct Input
{

	Button keyBoard[Button::BUTTONS_COUNT];

	bool focused = false;
};


void processInputAfter(Input &input);

void resetInput(Input &input);

//newState == 1 means pressed else released
void processEventButton(Button &b, bool newState);
