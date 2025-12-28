#include "chip8.h"
#include "display.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " <<  argv[0] << " <ROM> <Scale> <CPU Cycle Delay>" << std::endl;
		return 1;
	}

	//Extract arguments
	char* const romPath{ argv[1] };
	int videoScale{ std::stoi(argv[2]) };
	int cycleDelay{ std::stoi(argv[3]) };

	//Initialize display
	Display display("CHIP-8", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	//Initialize Chip8 & load ROM into memory
	Chip8 chip8;
	chip8.LoadROM(romPath);

	//Initialize video pitch (bytes per row of video buffer) & quit flag
 	int videoPitch{ static_cast<int>(sizeof(chip8.videoBuffer[0])) * VIDEO_WIDTH };
	bool quit{ false };

	while (!quit)
	{
		display.ProcessInput(chip8.keypad, quit);
		chip8.CPUCycle();
		display.Draw(chip8.videoBuffer, videoPitch);
		SDL_Delay(cycleDelay);
	}

	return 0;
}
