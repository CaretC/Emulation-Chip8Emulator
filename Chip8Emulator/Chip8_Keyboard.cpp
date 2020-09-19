#include "Chip8_Keyboard.h"

// Public
// ++++++
void Chip8_Keyboard::KeyDown(SDL_Keycode key)
{
    int mappedKey = mapKey(key);

    if (mappedKey != -1)
    {
        keyboard[mappedKey] = true;

        if (DEBUG_MODE == 1)
        {
            std::cout << "DEBUG: " << (char)key << " is down" << std::endl;
            std::cout << "DEBUG: Key state read = " << IsKeyDown(key) << std::endl;
        }
    }
}

void Chip8_Keyboard::KeyUp(SDL_Keycode key)
{
    int mappedKey = mapKey(key);

    if (mappedKey != -1)
    {
        keyboard[mappedKey] = false;

        if (DEBUG_MODE == 1)
        {
            std::cout << "DEBUG: " << (char)key << " is up" << std::endl;
            std::cout << "DEBUG: Key state read = " << IsKeyDown(key) << std::endl;
        }
    }
}

bool Chip8_Keyboard::IsKeyDown(SDL_Keycode key)
{
    int mappedKey = mapKey(key);

    if (mappedKey != -1)
    {
        return keyboard[mappedKey];
    }
    else
    {
        return false;
    }
}

// Private
// +++++++
int Chip8_Keyboard::mapKey(SDL_Keycode key)
{
    for (int i = 0; i < KEYBOARD_KEYS; i++)
    {
        if (keyMap[i] == key)
        {
            return i;
        }
    }

    return -1;
}