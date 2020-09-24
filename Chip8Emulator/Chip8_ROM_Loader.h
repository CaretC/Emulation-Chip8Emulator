#pragma once


#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#include"Chip8_Memory.h"
#include"config.h"

class Chip8_ROM_Loader
{
	public:
		void loadROM(Chip8_Memory* memory, std::string filepath);
};

