#ifndef PONG_HPP
#define PONG_HPP

// #include "Container.hpp"
// #include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

// class MenuState : public State {
// public:
//   MenuState(StateStack &stack, Context context);

//   virtual void draw();
//   virtual bool update(sf::Time dt);
//   virtual bool handleEvent(const sf::Event &event);

// private:
//   sf::Sprite mBackgroundSprite;
//   GUI::Container mGUIContainer;
// };

#pragma once

#include "State.hpp"
#include "PongEntity.hpp"
#include "PaddlePlayer.hpp"
#include "PongBall.hpp"
#include "PongScore.hpp"

class PingPong : public State {
public:
	//void Initialize(sf::RenderWindow* window);
	// void Update(sf::RenderWindow* window);
	// void Render(sf::RenderWindow* window);
	// void Destroy(sf::RenderWindow* window);
	// ~game();
	PingPong(StateStack &stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event &event);


	// virtual void Initialize(sf::RenderWindow* window);
	// virtual void Update(sf::RenderWindow* window);
	// virtual void Render(sf::RenderWindow* window);
	// virtual void Destroy(sf::RenderWindow* window);

private:
	paddle_player* player1;
	paddle_player* player2;
	ball* theBall;
	score* player1Score;
	score* player2Score;

	sf::Font* font;
};

#endif