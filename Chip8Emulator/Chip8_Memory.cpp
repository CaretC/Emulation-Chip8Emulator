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

unsigned char Chip8_Memory::GetMemoryByte(int index)
{
	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Geting byte from memory position " << index << std::endl;
	}

	return memory[index];
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
                  