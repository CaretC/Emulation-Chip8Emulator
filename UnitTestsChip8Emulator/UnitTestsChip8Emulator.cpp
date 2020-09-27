#include "pch.h"
#include "CppUnitTest.h"
#include"../Chip8Emulator/config.h"
#include"../Chip8Emulator/Chip8_Stack.h"
#include"../Chip8Emulator/Chip8_Registers.h"
#include"../Chip8Emulator/Chip8_Memory.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsChip8Emulator
{
	TEST_CLASS(UnitTestsChip8_Registers)
	{
		private:
			Chip8_Registers registers;
		public:
			TEST_METHOD(V_Registers)
			{
				for (int i = 0; i < NUMBER_OF_V_REGISTERS; i++)
				{
					registers.SetVRegister(i, i);
				}

				for (int i = 0; i < NUMBER_OF_V_REGISTERS; i++)
				{
					Assert().IsTrue(registers.GetVRegister(i) == i);
				}
			}

			TEST_METHOD(I_Register)
			{
				registers.SetIRegister(0x3000);
				Assert().IsTrue(registers.GetIRegister() == 0x3000);
			}

			TEST_METHOD(DT_Register)
			{
				registers.SetDTRegister(100);
				Assert().IsTrue(registers.GetDTRegister() == 100);
				registers.DecrementDTRegister();
				Assert().IsTrue(registers.GetDTRegister() == 99);
			}

			TEST_METHOD(ST_Register)
			{
				registers.SetSTRegister(100);
				Assert().IsTrue(registers.GetSTRegister() == 100);
				registers.DecrementSTRegister();
				Assert().IsTrue(registers.GetSTRegister() == 99);
			}

			TEST_METHOD(PC_Resgister)
			{
				registers.SetPCRegister(0x200);
				Assert().IsTrue(registers.GetPCRegister() == 0x200);
				registers.IncrementPCRegister();
				Assert().IsTrue(registers.GetPCRegister() == (0x200 + INSTRUCTION_LENGTH));
			}

			TEST_METHOD(SP_Register)
			{
				Assert().IsTrue(registers.GetSPRegister() == 0);
				registers.IncrementSPRegister();
				Assert().IsTrue(registers.GetSPRegister() == 1);
				registers.DecrementSPRegister();
				Assert().IsTrue(registers.GetSPRegister() == 0);
			}
	};

	TEST_CLASS(UnitTestsChip8_Stack)
	{
		private:
			Chip8_Stack stack;
			Chip8_Registers registers;
		public:
			TEST_METHOD(PushPop)
			{
				stack.Push(&registers, 10);
				Assert().IsTrue(registers.GetSPRegister() == 1);
				Assert().IsTrue(stack.Pop(&registers) == 10);
				Assert().IsTrue(registers.GetSPRegister() == 0);
			}
	};

	TEST_CLASS(UnitTestsChip8_Memory)
	{
		private:
			Chip8_Memory memory;
		public:
		TEST_METHOD(GetSetByte)
		{
			memory.SetMemoryByte(0x01, 0x10);
			Assert().IsTrue(memory.GetMemoryByte(0x01) == 0x10);
		}

		TEST_METHOD(SetBlock)
		{
			unsigned char testBlock[15];
			
			for (int i = 0; i < 15; i++)
			{
				testBlock[i] = 0x30 + i;
			}

			memory.SetMemoryBlock(testBlock, 0x200, 15);

			for (int i = 0; i < 15; i++)
			{
				Assert().IsTrue(memory.GetMemoryByte(0x200 + i) == 0x30 + i);
			}
		}

		TEST_METHOD(LoadInstruction)
		{
			memory.SetMemoryByte(0x33, 0x20);
			memory.SetMemoryByte(0x34, 0x30);

			unsigned short testInstruction = memory.GetMemoryByte(0x33) << 8 | memory.GetMemoryByte(0x34);
			Assert().IsTrue(testInstruction == memory.GetInstruction(0x33));
		}

		TEST_METHOD(GetSprite)
		{
			unsigned char testSprite[15];

			for (int i = 0; i < 15; i++)
			{
				testSprite[i] = 0x01 + i;
			}

			memory.SetMemoryBlock(testSprite, 0x300, 15);

			unsigned char sprite[15];

			memory.GetSprite(sprite, 0x300, 15);

			for (int i = 0; i < 15; i++)
			{
				Assert().IsTrue(testSprite[i] == sprite[i]);
			}
		}
	};

	TEST_CLASS(UnitTestsChip8_Keyboard)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};

	TEST_CLASS(UnitTestsChip8_Screen)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};

	TEST_CLASS(UnitTestsChip8_ROM_Loader)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};

	TEST_CLASS(UnitTestsChip8)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		}
	};
}
