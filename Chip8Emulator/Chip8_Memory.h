#pragma once
#include<iostream>

#include"config.h"

class Chip8_Memory
{
	private:
		unsigned char memory[MEMORY_SIZE] = { 0 };
	public:
		void SetMemoryByte(int index, unsigned char value);
		void SetMemoryBlock(const char data[], unsigned short loadStartAddress);
		unsigned char GetMemoryByte(int index);
		unsigned short GetInstruction(int index);
};

