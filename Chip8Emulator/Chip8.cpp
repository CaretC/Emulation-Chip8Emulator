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
	unsigned char tmp;
	unsigned short tmpL;

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

		case 0x9000:
			std::cout << "SNE Vx, Vy" << std::endl;
			if (registers.GetVRegister(x) != registers.GetVRegister(y)) registers.IncrementPCRegister();
			break;

		case 0xA000:
			std::cout << "LD I " << nnn << std::endl;
			registers.SetIRegister(nnn);
			break;

		case 0xB000:
			std::cout << "JP V0, addr" << std::endl;
			tmpL = nnn + registers.GetVRegister(0x00);
			registers.SetPCRegister(tmpL);
			break;
			
		case 0xC000:
			std::cout << "RND Vx, byte" << std::endl;
			srand(clock());
			registers.SetVRegister(x, ((rand() % 255) & kk));
			break;

		case 0xD000:
		{
			std::cout << "DRW Vx, Vy, nibble" << std::endl;
			unsigned char sprite[15] = { 0 };
			memory.GetSprite(sprite, registers.GetIRegister(), n);
			registers.SetVRegister(0x0F, screen.DrawSprite(
				registers.GetVRegister(x),
				registers.GetVRegister(y),
				sprite,
				n
			));
			break;
		}

		case 0xE000:
		{
			switch (opcode & 0x0FF)
			{
				case 0x9E:
					std::cout << "SKP Vx" << std::endl;
					if (keyboard.IsKeyDownInt(registers.GetVRegister(x))) registers.IncrementPCRegister();
					break;

				case 0xA1:
					std::cout << "SKNP Vx" << std::endl;
					if (!keyboard.IsKeyDownInt(registers.GetVRegister(x))) registers.IncrementPCRegister();
					break;
			}

			break;
		}

		case 0xF000:
			exectue0xF000(opcode, x);
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

void Chip8::exectue0xF000(unsigned short opcode, unsigned char x)
{
	switch (opcode & 0x0FF)
	{
		case 0x07:
			std::cout << "LD Vx, DT" << std::endl;
			registers.SetVRegister(x, registers.GetDTRegister());
			break;

		case 0x0A:			
			std::cout << "LD Vx, K" << std::endl;
			registers.SetVRegister(x, keyboard.MapKey(waitForKeyPress()));
			break;

		case 0x15:
			std::cout << "LD DT, Vx" << std::endl;
			registers.SetDTRegister(registers.GetVRegister(x));
			break;

		case 0x18:
			std::cout << "LD ST, Vx" << std::endl;
			registers.SetSTRegister(registers.GetVRegister(x));
			break;

		case 0x1E:
			std::cout << "ADD I, Vx" << std::endl;
			registers.SetIRegister(registers.GetIRegister() + registers.GetVRegister(x));
			break;

		case 0x29:
			std::cout << "LD F, Vx" << std::endl;
			registers.SetIRegister(0x00 + (5 * registers.GetVRegister(x)));
			break;

		case 0x33:
		{
			std::cout << "LD B, Vx" << std::endl;

			unsigned char hundreds = registers.GetVRegister(x) / 100;
			unsigned char tens = registers.GetVRegister(x) / 10 % 10;
			unsigned char units = registers.GetVRegister(x) % 10;

			memory.SetMemoryByte(registers.GetIRegister(), hundreds);
			memory.SetMemoryByte((registers.GetIRegister() + 1), tens);
			memory.SetMemoryByte((registers.GetIRegister() + 2), units);
			break;
		}

		case 0x55:
		{
			std::cout << "LD [I], Vx" << std::endl;

			for (int i = 0; i <= x; i++)
			{
				memory.SetMemoryByte((registers.GetIRegister() + i), registers.GetVRegister(i));
			}

			break;
		}

		case 0x65:
		{
			std::cout << "LD Vx, [I]" << std::endl;

			for (int i = 0; i <= x; i++)
			{
				registers.SetVRegister(i, memory.GetMemoryByte(registers.GetIRegister() + i));
			}

			break;
		}
	}
}

SDL_Keycode Chip8::waitForKeyPress()
{
	SDL_Event event;

	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (keyboard.IsValidKey(event.key.keysym.sym))
			{
				return event.key.keysym.sym;
			}
		}
	}
}
