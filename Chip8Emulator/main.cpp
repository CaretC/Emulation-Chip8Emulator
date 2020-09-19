/*

*/

// Includes
// ========
#include<iostream>
#include<SDL.h>

#include"config.h"

// Main()
// ======
int main(int argc, char* args[])
{
	// Variables
	// ---------


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
			}
		}
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
