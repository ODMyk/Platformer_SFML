#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>

#include "CommandQueue.hpp"

class Player {
public:
	Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
};

#endif
