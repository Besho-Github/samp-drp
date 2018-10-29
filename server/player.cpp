#include "player.h"

Player::Player()
{
	this->details = Hooks::Application::details;
	this->state = Hooks::Application::state;
	this->large_image = Hooks::Application::large_image;
	this->large_image_text = Hooks::Application::large_image_text;
	this->small_image = Hooks::Application::small_image;
	this->small_image_text = Hooks::Application::small_image_text;
}

std::unordered_map<WORD, std::shared_ptr<Player>> Players;