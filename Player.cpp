#include <iostream>

#include "Avatar.hpp"
#include "Category.hpp"
#include "Command.hpp"
#include "Player.hpp"
#include <cmath>

struct BodyMover {
	BodyMover(float x, float y): velocity(x, y) {}
	void operator () (Avatar& body, sf::Time dt) const {
		body.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player() {}

void Player::handleRealtimeInput(CommandQueue &commands) {
	const float playerSpeed = 450.f;

	bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	sf::Vector2f movement(0.f, 0.f);

	movement.x = playerSpeed * (D - A);
	movement.y = playerSpeed * (S - W);

	if (movement.x && movement.y) {
		movement.x /= sqrt(2);
		movement.y /= sqrt(2);
	}

	Command move;
	move.category = Category::Player;
	move.action = derivedAction<Avatar>(BodyMover(movement.x, movement.y));

	commands.push(move);
	}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		Command out;
		out.category = Category::Player;
		out.action = [] (SceneNode& node, sf::Time) {
			std::cout << node.getPosition().x << " " << node.getPosition().y << std::endl;
		};
		commands.push(out);
	}
}
