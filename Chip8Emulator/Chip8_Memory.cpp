#include "Chip8_Memory.h"

void Chip8_Memory::SetMemoryByte(int index, unsigned char value)
{
	// Store value at memory address
	memory[index] = value;

	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Storing " << std::hex << value << "at memory position "
			<< index << std::endl;
	}
}

void Chip8_Memory::SetMemoryBlock(unsigned char data[], unsigned short loadStartAddress, int blockSize)
{
	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Storing " << blockSize << " bytes in memory starting at address "
			<< std::hex << loadStartAddress << std::endl;
	}

	memcpy(&memory[loadStartAddress], data, blockSize);
}


unsigned char Chip8_Memory::GetMemoryByte(int index)
{
	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Geting byte from memory position " << index << std::endl;
	}

	return memory[index];
}

void Chip8_Memory::GetSprite(unsigned char (&block)[15], unsigned short startAddress, int blockSize)
{
	for (int i = 0; i < blockSize; i++)
	{
		block[i] = memory[startAddress + i];
	}
}

unsigned short Chip8_Memory::GetInstruction(int index)
{
	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Getting instruction from memory positions " << index
			<< " and " << index + 1 << std::endl;
	}

	unsigned char byte1 = GetMemoryByte(index);
	unsigned char byte2 = GetMemoryByte(index + 1);

	return byte1 << 8 | byte2;
}
                  