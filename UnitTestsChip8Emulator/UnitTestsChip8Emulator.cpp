#include "pch.h"
#include "CppUnitTest.h"
#include"../Chip8Emulator/Chip8_Stack.h"
#include"../Chip8Emulator/Chip8_Registers.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsChip8Emulator
{
	TEST_CLASS(UnitTestsChip8_Registers)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
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
	public:

		TEST_METHOD(TestMethod1)
		{
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
