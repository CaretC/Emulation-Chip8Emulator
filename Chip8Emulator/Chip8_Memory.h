#pragma once
#include<iostream>

#include"config.h"

class Chip8_Memory
{
	private:
		unsigned char memory[MEMORY_SIZE];
	public:
		void SetMemoryByte(int index, unsigned char value);
		unsigned char GetMemoryByte(int index);
		unsigned short GetInstruction(int index);
};

