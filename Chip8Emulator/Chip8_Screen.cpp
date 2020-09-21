#include "Chip8_Screen.h"

// Public
// ++++++
void Chip8_Screen::Clear()
{
    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Clearing Screen buffer..." << std::endl;
    }

    for (int x = 0; x < CHIP8_WIDTH; x++)
    {
        for (int y = 0; y < CHIP8_HEIGHT; y++)
        {
            screenBuffer[x][y] = false;
        }
    }
}

void Chip8_Screen::SetPixel(int x, int y, bool val)
{
    isInBounds(x, y);

    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Setting pixel " << x << "," << y << " to " << val << std::endl;
    }

    screenBuffer[x][y] = val;
}

bool Chip8_Screen::PixelIsSet(int x, int y)
{
    isInBounds(x, y);

    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Checking screen buffer value at " << x << "," << y << std::endl;
    }

    return screenBuffer[x][y];
}

// Draws spite to screen buffer, if there is a sprite collision returns true
bool Chip8_Screen::DrawSprite(int x, int y, unsigned char sprite[], int spriteSize)
{
    bool spriteCollisionDetected = false;

    // Load byte from sprite
    for (int ly = 0; ly < spriteSize; ly++)
    {
        char spriteByte = sprite[ly];

        // Itterate through spriteByte bits and set screen buffer as needed
        for (int lx = 0; lx < 8; lx++)
        {
            if ((spriteByte & (0b10000000 >> lx)) == 0)
            {
                //  Do Nothing
            }
            else
            {
                // Calculate position but also ensure that if it extends beyond the
                // buffer it wraps
                int xPos = (lx + x) % CHIP8_WIDTH;
                int yPos = (ly + y) % CHIP8_HEIGHT;

                // Check for sprite pixle collision
                if (screenBuffer[xPos][yPos])
                {
                    spriteCollisionDetected = true;
                }

                // XOR the sprite buffer
                screenBuffer[xPos][yPos] ^= true;
            }
        }
    }

    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Printing sprite" << std::endl;

        if (spriteCollisionDetected)
        {
            std::cout << "DEBUG: Sprite collision detected" << std::endl;
        }
    }

    return spriteCollisionDetected;
}

void Chip8_Screen::GetScreenBuffer(bool (&buffer)[CHIP8_WIDTH][CHIP8_HEIGHT])
{
    for (int x = 0; x < CHIP8_WIDTH; x++)
    {
        for (int y = 0; y < CHIP8_HEIGHT; y++)
        {
            buffer[x][y] = screenBuffer[x][y];
        }
    }
}

// Private
// +++++++
void Chip8_Screen::isInBounds(int x, int y)
{
    assert(
        x >= 0 && x < CHIP8_WIDTH &&
        y >=0 && y < CHIP8_HEIGHT &&
        "Assersion failed: Pixel outside of screen buffer index."
    );
}