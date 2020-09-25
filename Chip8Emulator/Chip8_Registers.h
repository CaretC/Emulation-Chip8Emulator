#pragma once
#include<assert.h>
#include "config.h"

class Chip8_Registers
{
	private:
		unsigned char V[NUMBER_OF_V_REGISTERS] = { 0 };
		unsigned short I = 0;
		unsigned char DT = 0; // Delay Timer
		unsigned char ST = 0; // Sound Timer
		unsigned short PC = CHIP8_PROGRAMME_ENTRY_POINT; // Programme Counter
		unsigned char SP = 0;

		// Checks the index is below NUMBER_OF_V_REGISTERS
		void indexInBounds(int index);

	public:
		//  V
		// ===
		void SetVRegister(int index, unsigned char value);
		unsigned char GetVRegister(unsigned char index);

		//  I 
		// ===
		void SetIRegister(unsigned short value);
		unsigned short GetIRegister();

		//  DT
		// ====
		void SetDTRegister(unsigned char value);
		void DecrementDTRegister();
		unsigned char GetDTRegister();

		//  ST
		// ====
		void SetSTRegister(unsigned char value);
		void DecrementSTRegister();
		unsigned char GetSTRegister();

		//  PC
		// ====
		void SetPCRegister(unsigned short value);
		void IncrementPCRegister();
		unsigned short GetPCRegister();

		//  SP
		// ====
		void IncrementSPRegister();
		void DecrementSPRegister();
		unsigned char GetSPRegister();
		
};

