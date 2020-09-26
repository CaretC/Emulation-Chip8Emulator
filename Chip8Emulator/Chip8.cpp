#include "Chip8.h"

// Public
// ++++++
void Chip8::Initialize()
{
	std::cout << "Initializing CHIP-8..." << std::endl;	
	loadDefaultCharacterSet();
}

void Chip8::Execute(unsigned short opcode)
{
	if (DEBUG_MODE == 1)
	{
		std::cout << "DEBUG: Executing opcode 0x" << std::hex << (int)opcode << std::endl;
	}

	switch (opcode)
	{
		case 0x00E0:
			std::cout << "CLS" << std::endl;
			screen.Clear();
			break;

		case 0x00EE:
			std::cout << "RET" << std::endl;
			registers.SetPCRegister(stack.Pop(&registers));

		default:
			executeExtended(opcode);
			break;
	}
}



// Private
// +++++++
void Chip8::loadDefaultCharacterSet()
{
	std::cout << "Loading default character set into memory..." << std::endl;
	memory.SetMemoryBlock(defaultCharacterSet, 0x00, 80);
	std::cout << "Default character set loaded" << std::endl;
}

void Chip8::executeExtended(unsigned short opcode)
{
	// Parse relevant parameters
	unsigned short nnn = opcode & 0x0FFF;
	unsigned char x = opcode >> 8 & 0x000F;
	unsigned char y = opcode >> (8 + 4) & 0x000F;
	unsigned short kk = opcode & 0x00FF;
	unsigned char n = opcode & 0x000F;

	switch (opcode & 0xF000)
	{
		case 0x1000:
			std::cout << "JP " << nnn << std::endl;
			registers.SetPCRegister(nnn);
			break;

		case 0x2000:
			std::cout << "CALL " << nnn << std::endl;
			stack.Push(&registers, registers.GetPCRegister());
			registers.SetPCRegister(nnn);
			break;

		case 0x3000:
			std::cout << "SE" << std::endl;
			if (registers.GetVRegister(x) == kk) registers.IncrementPCRegister();
			break;

		case 0x4000:
			std::cout << "SNE" << std::endl;
			if (registers.GetVRegister(x) != kk) registers.IncrementPCRegister();
			break;

		case 0x5000:
			std::cout << "SE Vx Vy" << std::endl;
			if (registers.GetVRegister(x) == registers.GetVRegister(y)) registers.IncrementPCRegister();
			break;

		case 0x6000:
			std::cout << "LD" << (int)x << " " << kk << std::endl;
			registers.SetVRegister(x, kk);
			break;

		case 0x7000:
			std::cout << "ADD " << (int)x << kk << std::endl;
			registers.SetVRegister(x, (registers.GetVRegister(x) + kk));
			break;

		case 0x8000:
			exectue0x8000(opcode, x, y);
			break;

	}
}

void Chip8::exectue0x8000(unsigned short opcode, unsigned char x, unsigned char y)
{
	unsigned char tmp;
	unsigned short tmpL;

	switch (opcode & 0x000F)
	{
		case 0x00:
			std::cout << "LD Vx Vy" << std::endl;
			registers.SetVRegister(x, registers.GetVRegister(y));
			break;

		case 0x01:
			std::cout << "OR Vx Vy" << std::endl;
			tmp = registers.GetVRegister(x) | registers.GetVRegister(y);
			registers.SetVRegister(x, tmp);
			break;

		case 0x02:
			std::cout << "AND Vx Vy" << std::endl;
			tmp = registers.GetVRegister(x) & registers.GetVRegister(y);
			registers.SetVRegister(x, tmp);
			break;

		case 0x03:
			std::cout << "XOR Vx Vy" << std::endl;
			tmp = registers.GetVRegister(x) ^ registers.GetVRegister(y);
			registers.SetVRegister(x, tmp);
			break;

		case 0x04:
			std::cout << "ADD Vx Vy" << std::endl;
			tmpL = registers.GetVRegister(x) + registers.GetVRegister(y);
			if (tmpL > 255) registers.SetVRegister(0x0F, 1);
			registers.SetVRegister(x, tmpL);
			break;

		case 0x05:
			std::cout << "SUB Vx Vy" << std::endl;
			tmpL = registers.GetVRegister(x) - registers.GetVRegister(y);
			if(registers.GetVRegister(x) > registers.GetVRegister(y)) registers.SetVRegister(0x0F, 1);
			break;

		case 0x06:
			std::cout << "SHR Vx {, Vy}" << std::endl;
			registers.SetVRegister(0x0F, (registers.GetVRegister(x) & 0x01));
			registers.SetVRegister(x, (registers.GetVRegister(x) / 2));
			break;

		case 0x07:
			std::cout << "SUBN Vx, Vy" << std::endl;
			if (registers.GetVRegister(y) > registers.GetVRegister(x)) registers.SetVRegister(0x0F, 1);
			registers.SetVRegister(x, (registers.GetVRegister(y) - registers.GetVRegister(x)));
			break;

		case 0x0E:
			std::cout << "SHL Vx {, Vy}" << std::endl;
			registers.SetVRegister(0x0F, (registers.GetVRegister(x) & 0x100000000));
			registers.SetVRegister(x, (registers.GetVRegister(x) * 2));
			break;
	}
}
