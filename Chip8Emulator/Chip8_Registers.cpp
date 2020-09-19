#include "Chip8_Registers.h"

// Public
// ++++++

// V Registers
// ============
void Chip8_Registers::SetVRegister(int index, unsigned char value)
{
    // Check index is in bounds
    indexInBounds(index);

    // Set register at index
    V[index] = value;
}

unsigned char Chip8_Registers::GetVRegister(int index)
{
    // Check index is in bounds
    indexInBounds(index);

    // Return register at index
    return V[index];
}

// I Register
// ==========
void Chip8_Registers::SetIRegister(unsigned short value)
{
    // Set I register
    I = value;
}

unsigned short Chip8_Registers::GetIRegister()
{
    // Return I register
    return I;
}

// Delay Timer Register
// ====================
void Chip8_Registers::SetDTRegister(unsigned char value)
{
    // Set Delay Timer Register
    DT = value;
}

unsigned char Chip8_Registers::GetDTRegister()
{
    // Return Delay Timer Register
    return DT;
}

// Sound Timer Register
// ====================
void Chip8_Registers::SetSTRegister(unsigned char value)
{
    // Set Sound Timer Register
    ST = value;
}

unsigned char Chip8_Registers::GetSTRegister()
{
    // Return Sound Timer Register
    return ST;
}

// Programme Counter Register
// ==========================
void Chip8_Registers::SetPCRegister(unsigned short value)
{
    // Set Programme Counter Register
    PC = value;
}

void Chip8_Registers::IncrementPCRegister()
{
    // Increment the Programme Counter by instruction length
    PC += INSTRUCTION_LENGTH;
}

unsigned short Chip8_Registers::GetPCRegister()
{
    // Return Programme Counter register
    return PC;
}

// Stack Pointer Register
// ======================
void Chip8_Registers::IncrementSPRegister()
{
    // Increment Stack Pointer register
    SP++;
}

void Chip8_Registers::DecrementSPRegister()
{
    // Decrement Stack Pointer
    SP--;
}

unsigned char Chip8_Registers::GetSPRegister()
{
    // Return Stack Pointer
    return SP;
}

// Private
// +++++++
void Chip8_Registers::indexInBounds(int index)
{
    assert(index < NUMBER_OF_V_REGISTERS && "Assetion Failed: V register index out of bounds.");
}
