#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants
{
    // Constants
   	constexpr int gScreenWidth     { 640 };
   	constexpr int gScreenHeight    { 480 };
   	// PATH TO YOUR RESOURCE FOLDER 'resources', 'gResPath'
   	const std::string gResPath { "./resources/" };
	// PATH'S TO ALL YOUR EXTERNAL RESOURCES using 'gResPath'
	const std::string bg_str  { gResPath + "images/bg.jpg" };

	const std::string font_str {gResPath + "fonts/font.ttf"};
    
	const std::string mainMenu_str   { gResPath + "sounds/MainMenu.wav" };
	const std::string pausMusic_str  { gResPath + "sounds/PausMusic.wav" };
	const std::string sample_str     { gResPath + "sounds/sample.wav" };

	const std::string snakebite1_str { gResPath + "sounds/Snakebite1.wav" };
	const std::string snakebite2_str { gResPath + "sounds/Snakebite2.wav" };
	const std::string snakebite3_str { gResPath + "sounds/Snakebite3.wav" };
	const std::string snakebite4_str { gResPath + "sounds/Snakebite4.wav" };
	const std::string snakebite5_str { gResPath + "sounds/Snakebite5.wav" };
	const std::string snakebite6_str { gResPath + "sounds/Snakebite6.wav" };
	const std::string snakebite7_str { gResPath + "sounds/Snakebite7.wav" };
	const std::string snakebite8_str { gResPath + "sounds/Snakebite8.wav" };

	const std::string snakemusik_str { gResPath + "sounds/Snakemusik.wav" };
}

#endif