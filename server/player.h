#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

struct Player
{
	Player();

	std::string details;
	std::string state;
	std::string large_image;
	std::string large_image_text;
	std::string small_image;
	std::string small_image_text;
};

extern std::unordered_map<WORD, std::shared_ptr<Player>> Players;
#endif