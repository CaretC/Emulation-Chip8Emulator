/*

*/

// Includes
// ========
#include<iostream>
#include<SDL.h>
#include<Windows.h>
#include<string>

#include"config.h"
#include"Chip8.h"
#include"Chip8_ROM_Loader.h"

// Function Prototypes
// ====================
void DrawPixel(SDL_Renderer* renderer, int x, int y);
void DrawSprite(Chip8* chip8, int x, int y, unsigned short memoryAddress, int spriteSize);

// Main()
// ======
int main(int argc, char* args[])
{
	// CHIP-8
	// ------
	Chip8 chip8;
	chip8.Initialize();
	bool screenBuffer[CHIP8_WIDTH][CHIP8_HEIGHT] = { 0 };

	// TODO: Remove Test
	std::string romPath = "missile.ch8";
	Chip8_ROM_Loader romLoader;
	romLoader.loadROM(&chip8.memory, romPath);
	
	// SDL Variables
	// -------------
	const int SCREEN_WIDTH = CHIP8_WIDTH * CHIP8_SCALE;
	const int SCREEN_HEIGHT = CHIP8_HEIGHT * CHIP8_SCALE;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// SDL Init
	// --------
	std::cout << "Initializing SDL..." << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized successfully" << std::endl;
	}
	else {
		std::cout << "ERROR: SDL did not initialize " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Create SDL Window
	// -----------------
	std::cout << "Creating SDL window..." << std::endl;

	window = SDL_CreateWindow(
		WINDOW_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN	
	);

	// TODO: Add check that window was created successfully

	std::cout << "SDL window created..." << std::endl;

	// Create SDL Renderer
	// -------------------
	std::cout << "Creating SDL renderer..." << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
	std::cout << "SDL renderer created" << std::endl;

	// Game Loop
	// ---------
	std::cout << "Entering game loop..." << std::endl;

	while (1)
	{
		// Handle SDL Events
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					goto out;
					break;

				case SDL_KEYDOWN:
					chip8.keyboard.KeyDown(event.key.keysym.sym);
					break;

				case SDL_KEYUP:
					chip8.keyboard.KeyUp(event.key.keysym.sym);
					break;
			}
		}

		// Render Pixels
		// -------------
		// Get screen buffer
		chip8.screen.GetScreenBuffer(screenBuffer);

		// Clear
		SDL_SetRenderDrawColor(renderer, 155, 188, 15, 0);
		SDL_RenderClear(renderer);

		// Draw Pixels
		SDL_SetRenderDrawColor(renderer, 48, 98, 48, 0);

		for (int x = 0; x < CHIP8_WIDTH; x++)
		{
			for (int y = 0; y < CHIP8_HEIGHT; y++)
			{
				if (screenBuffer[x][y])
				{
					DrawPixel(renderer, x, y);
				}
			}
		}

		// Render to screen
		SDL_RenderPresent(renderer);
		// TODO: Put RenderPixcels into a function to neaten up

		// Delay Timer
		if (chip8.registers.GetDTRegister() > 0)
		{
			if (DEBUG_MODE == 1)
			{
				std::cout << "DEBUG: DELAY..." << std::endl;
				Sleep(CHIP8_DELAY);
				chip8.registers.DecrementDTRegister();
			}
		}

		// Sound Timer
		if (chip8.registers.GetSTRegister() > 0)
		{
			if (DEBUG_MODE == 1)
			{
				std::cout << "DEBUG: BEEP" << std::endl;
			}

			Beep(800, (100 * chip8.registers.GetSTRegister()));
			chip8.registers.SetSTRegister(0);
		}

		// Fetch and execute opcode
		unsigned short opcode = chip8.memory.GetInstruction(chip8.registers.GetPCRegister());
		chip8.Execute(opcode);
		chip8.registers.IncrementPCRegister();
	}

out:
	std::cout << "Exited game loop..." << std::endl;

	// Cleanup
	// -------
	std::cout << "Cleaning up components..." << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	std::cout << "Cleanup complete" << std::endl;

	// Exit Main
	// ---------
	std::cout << "Exiting programme..." << std::endl;
	return 0;
}

// Functions
// =========
void DrawPixel(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect pixel;
	pixel.x = x * CHIP8_SCALE;
	pixel.y = y * CHIP8_SCALE;
	pixel.w = CHIP8_SCALE;
	pixel.h = CHIP8_SCALE;
	SDL_RenderFillRect(renderer, &pixel);
}

void DrawSprite(Chip8* chip8, int x, int y, unsigned short memoryAddress, int spriteSize)
{
	unsigned char sprite[15] = { 0 };

	chip8->memory.GetSprite(sprite, memoryAddress, spriteSize);
	chip8->screen.DrawSprite(x, y, sprite, spriteSize);
}