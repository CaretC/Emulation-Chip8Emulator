#pragma once
#include<iostream>

#include"Chip8_Registers.h"
#include"Chip8_Memory.h"
#include"Chip8_Stack.h"
#include"Chip8_Keyboard.h"

class Chip8
{
	public:
		Chip8_Registers registers;
		Chip8_Memory memory;
		Chip8_Stack stack;
		Chip8_Keyboard keyboard;

		void Initialize();

	private:
		const char defaultCharacterSet[16 * 5] = {
        (const char)0xF0, (const char)0x90, (const char)0x90, (const char)0x90, (const char)0xF0, // "0"
		(const char)0x20, (const char)0x60, (const char)0x20, (const char)0x20, (const char)0x70, // "1"
		(const char)0xF0, (const char)0x10, (const char)0xF0, (const char)0x80, (const char)0xF0, // "2"
		(const char)0xF0, (const char)0x10, (const char)0xF0, (const char)0x10, (const char)0xF0, // "3"
		(const char)0x90, (const char)0x90, (const char)0xF0, (const char)0x10, (const char)0x10, // "4"
		(const char)0xF0, (const char)0x80, (const char)0xF0, (const char)0x10, (const char)0xF0, // "5"
		(const char)0xF0, (const char)0x80, (const char)0xF0, (const char)0x90, (const char)0xF0, // "6"
		(const char)0xF0, (const char)0x10, (const char)0x20, (const char)0x40, (const char)0x40, // "7"
		(const char)0xF0, (const char)0x90, (const char)0xF0, (const char)0x90, (const char)0xF0, // "8"
		(const char)0xF0, (const char)0x90, (const char)0xF0, (const char)0x10, (const char)0xF0, // "9"
		(const char)0xF0, (const char)0x90, (const char)0xF0, (const char)0x90, (const char)0x90, // "A"
		(const char)0xE0, (const char)0x90, (const char)0xE0, (const char)0x90, (const char)0xE0, // "B"
		(const char)0xF0, (const char)0x80, (const char)0x80, (const char)0x80, (const char)0xF0, // "C"
		(const char)0xE0, (const char)0x90, (const char)0x90, (const char)0x90, (const char)0xE0, // "D"
		(const char)0xF0, (const char)0x80, (const char)0xF0, (const char)0x80, (const char)0xF0, // "E"
		(const char)0xF0, (const char)0x80, (const char)0xF0, (const char)0x80, (const char)0x80  // "F"
		};

		void loadDefaultCharacterSet();
};

