#ifndef PONGBALL_HPP
#define PONGBALL_HPP

#pragma once
#include "PaddlePlayer.hpp"
#include "PongScore.hpp"

class ball : public PongEntity {
public:
	ball(paddle_player* player1, paddle_player* player2, score* scorePlayer1, score* scorePlayer2);
	void update(sf::RenderWindow* window);
private:
	void resetposition(sf::RenderWindow* window);
	score* score1;
	score* score2;

	// reference to both paddles
	paddle_player* player1;
	paddle_player* player2;
};

#endif