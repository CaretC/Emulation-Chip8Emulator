#include "Chip8_Keyboard.h"

// Public
// ++++++
void Chip8_Keyboard::KeyDown(SDL_Keycode key)
{
    int mappedKey = MapKey(key);

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
    int mappedKey = MapKey(key);

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
    int mappedKey = MapKey(key);

    if (mappedKey != -1)
    {
        return keyboard[mappedKey];
    }
    else
    {
        return false;
    }
}

bool Chip8_Keyboard::IsKeyDownInt(int key)
{
    if (key < KEYBOARD_KEYS)
    {
        return keyboard[key];
    }
    else
    {
        return false;
    }
}

bool Chip8_Keyboard::IsValidKey(SDL_Keycode key)
{
    for (int i = 0; i < KEYBOARD_KEYS; i++)
    {
        if (keyMap[i] == key)
        {
            return true;
        }
    }

    return false;
}

int Chip8_Keyboard::MapKey(SDL_Keycode key)
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