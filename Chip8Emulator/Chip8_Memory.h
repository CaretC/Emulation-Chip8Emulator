#pragma once
#include<iostream>
#include <iterator>

#include"config.h"

class Chip8_Memory
{
	private:
		unsigned char memory[MEMORY_SIZE] = { 0 };
	public:
		void SetMemoryByte(int index, unsigned char value);
		void SetMemoryBlock(unsigned char data[], unsigned short loadStartAddress, int blockSize);
		unsigned char GetMemoryByte(int index);
		void GetMemoryBlock(unsigned char (&block)[15], unsigned short startAddress, int blockSize);
		unsigned short GetInstruction(int index);
};

