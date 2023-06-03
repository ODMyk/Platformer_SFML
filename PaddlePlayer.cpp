#include "PaddlePlayer.hpp"
#include <iostream>

paddle_player::paddle_player(int player) {
		this->playerNumber = player;
		switch (playerNumber) {
			// player 1
		case 0:
			this->Load("img/pp-p1-test.png");
			break;

			// player 2
		default:
			this->Load("img/pp-p2-test.png");
			break;
		}
	}

void paddle_player::update() {

		// each player has different player controls
		switch (this->playerNumber)
		{
		case 0:
			// one player uses the arrow keys
			this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))*7;
			break;
		default:
			// the other uses w and s
			this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))*7;
			break;
		}

		// make sure the paddle calls the superclass' update to make things move
		PongEntity::update();


		// make sure the paddles can't go off screen (experimental)
		if (this->getPosition().y < 0) {
            // std::cout << "! " << getGlobalBounds().height << "\n";
			this->move(0, 5);

		}

		if (this->getPosition().y + this->getGlobalBounds().height > 725) {
            // std::cout << "! " << this->getGlobalBounds().height << " " << this->getGlobalBounds().height + this->getPosition().y << "\n";
			this->move(0, -5);

		}
};