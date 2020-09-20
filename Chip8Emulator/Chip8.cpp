#include "Chip8.h"

// Public
// ++++++
void Chip8::Initialize()
{
	std::cout << "Initializing CHIP-8..." << std::endl;	
	loadDefaultCharacterSet();
}

// Private
// +++++++
void Chip8::loadDefaultCharacterSet()
{
	std::cout << "Loading default character set into memory..." << std::endl;
	memory.SetMemoryBlock(defaultCharacterSet, 0x00);
	std::cout << "Default character set loaded" << std::endl;
}
