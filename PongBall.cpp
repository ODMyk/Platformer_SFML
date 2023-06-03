#include "PongBall.hpp"
#include <iostream>
#include <cmath>

ball::ball(paddle_player* player1, paddle_player* player2, score* scorePlayer1, score* scorePlayer2){
	// set players
	this->player1 = player1;
	this->player2 = player2;
	// set scores
	this->score1 = scorePlayer1;
	this->score2 = scorePlayer2;
	this->Load("img/pp-ball.png");
	this->velocity.x = 5;
	this->velocity.y = 5;
}

void ball::update(sf::RenderWindow* window) {
	srand(time(NULL));
	// collision detection (super experimental)

	if (this->checkCollision(this->player1) || this->checkCollision(this->player2)) {
		// experimental speed increment
		int dir = this->velocity.x / abs(this->velocity.x) * -1;
		this->velocity.x = abs(velocity.x) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
		velocity.x *= dir;

		velocity.y += static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));

		// std::cout << "velocity: " << velocity.x << std::endl;
	}
	// if it hits the ceiling
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y) {
		this->velocity.y *= -1;
	}

	// see whether the players have scored a point
	// player 2 scores
	if (this->getPosition().x < 50) {
		this->score2->addScore();
		this->resetposition(window);
	}
	// player 1 scores
	if (this->getPosition().x > window->getSize().x - 50) {
		this->score1->addScore();
		this->resetposition(window);
	}
	PongEntity::update();
}

void ball::resetposition(sf::RenderWindow* window) {
	// random position after reset
	srand(time(NULL));
	this->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	velocity.x = 5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
	if (rand() % 2 == 0) {
		velocity.x *= -1;
	}
	velocity.y = 5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
	if (rand() % 2 == 0) {
		velocity.y *= -1;
	}
	std::cout << velocity.x << " "<< velocity.y << std::endl;

}