#pragma once
#include"Chip8_Registers.h"
#include"Chip8_Memory.h"
#include"Chip8_Stack.h"
#include"Chip8_Keyboard.h"

class Chip8
{
	public:
		Chip8_Registers registers;
		Chip8_Memory memory;
		Chip8_Stack stack;
		Chip8_Keyboard keyboard;
};

