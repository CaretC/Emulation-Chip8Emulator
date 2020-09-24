#include "Chip8_ROM_Loader.h"

// Public
// ++++++
void Chip8_ROM_Loader::loadROM(Chip8_Memory* memory, std::string filepath)
{
	// Open file and skip to end to get file size, close once done
	std::ifstream romFile;
	romFile.open(filepath, std::ios_base::binary | std::ios_base::ate);
	int fileSize = romFile.tellg();
	romFile.close();

	// Re-open the file at the start of file
	romFile.open(filepath, std::ios_base::in | std::ios_base::binary);
	
	// Dynamically define array on the heap to read in data to 
	char* buffer = new char[fileSize];

	// If the file is open then read it into buffer
	if (romFile)
	{		
		std::cout << "ROM file found" << std::endl;
		std::cout << "Reading " << fileSize << " bytes from ROM file " << filepath << "..." << std::endl;
		romFile.read(buffer, fileSize);
		// TODO: A nice to have is if it could load the title of the ROM to the window name
		std::cout << "ROM file read complete" << std::endl;
	}
	else
	{
		std::cout << "ROM file read error" << std::endl;
		delete buffer;
		exit(-1);
	}

	// Convert buffer to unsigned char array
	unsigned char* convertedBuffer = new unsigned char[fileSize];

	std::cout << "Loading ROM into CHIP-8 memory..." << std::endl;
	
	for (int i = 0; i < fileSize; i++)
	{
		convertedBuffer[i] = (unsigned char)buffer[i];
	}

	// Load ROM data to CHIP-8 memory
	int buffIndex = 0;
	for (int i = CHIP8_ROM_LOAD_ADDRESS; i < fileSize; i += 0x001)
	{
		memory->SetMemoryByte(i, convertedBuffer[buffIndex]);
		buffIndex++;
	}
	
	// Clean up heap data
	delete buffer;
	delete convertedBuffer;
	std::cout << "ROM loaded into CHIP-8 memory" << std::endl;
}
