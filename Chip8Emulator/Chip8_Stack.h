#pragma once
#include<assert.h>
#include<iostream>

#include"config.h"
#include"Chip8_Registers.h"

class Chip8_Stack
{
	private:
		unsigned short stack[MAX_STACK_DEPTH];
		void isInBounds(unsigned char index);

	public:
		void Push(Chip8_Registers* registers, unsigned short value);
		unsigned short Pop(Chip8_Registers* registers);
};

