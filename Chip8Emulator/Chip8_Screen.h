#pragma once
#include<iostream>
#include<assert.h>

#include"config.h"

class Chip8_Screen
{
	private:
		bool screenBuffer[CHIP8_WIDTH][CHIP8_HEIGHT] = { 0 };
		void isInBounds(int x, int y);

	public:
		void Clear();
		void SetPixel(int x, int y, bool val);
		bool PixelIsSet(int x, int y);
		bool DrawSprite(int x, int y, unsigned char sprite[], int spriteSize);
		void GetScreenBuffer(bool (&buffer)[CHIP8_WIDTH][CHIP8_HEIGHT]);		
};

