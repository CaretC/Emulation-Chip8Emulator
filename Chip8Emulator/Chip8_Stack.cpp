#include "Chip8_Stack.h"

// Public
// ++++++
void Chip8_Stack::Push(Chip8_Registers* registers, unsigned short value)
{
    isInBounds(registers->GetSPRegister());

    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Pushing " << value << " to stack index " << (int)registers->GetSPRegister() << std::endl;
    }

    stack[registers->GetSPRegister()] = value;

    registers->IncrementSPRegister();

}

unsigned short Chip8_Stack::Pop(Chip8_Registers* registers)
{
    isInBounds(registers->GetSPRegister());

    registers->DecrementSPRegister();

    if (DEBUG_MODE == 1)
    {
        std::cout << "DEBUG: Popping value from stack index " << (int)registers->GetSPRegister() << std::endl;
    }

    return stack[registers->GetSPRegister()];
}

// Private
// +++++++
void Chip8_Stack::isInBounds(unsigned char index)
{
    assert(index < MAX_STACK_DEPTH && "Asset Failed: Stack index out of bounds");
}