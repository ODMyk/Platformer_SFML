#pragma once
#include "Avatar.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time timedelta);
	void updateStatistics(sf::Time timedelta);
	void render();

private:
	Avatar* mPlayer;
	bool mIsPaused;

	sf::RenderWindow mWindow;
	World mWorld;
	const sf::Time FrameTime;
	
	sf::Time statTime;
	int framesCount;
	sf::Font mFont;
	sf::Text textFPS;
};
