#pragma once
#include<SDL.h>
#include<string>
#include<iostream>

#include"config.h"

class Chip8_Keyboard
{
	private:
		bool keyboard[KEYBOARD_KEYS];

		const char keyMap[KEYBOARD_KEYS] =
		{
			SDLK_0,
			SDLK_1,
			SDLK_2,
			SDLK_3,
			SDLK_4,
			SDLK_5,
			SDLK_6,
			SDLK_7,
			SDLK_8,
			SDLK_9,
			SDLK_a,
			SDLK_b,
			SDLK_c,
			SDLK_d,
			SDLK_e,
			SDLK_f
		};

		

	public:
		int MapKey(SDL_Keycode key);
		void KeyDown(SDL_Keycode key);
		void KeyUp(SDL_Keycode key);
		bool IsKeyDown(SDL_Keycode key);
		bool IsKeyDownInt(int key);
		bool IsValidKey(SDL_Keycode key);
};

