#ifndef PONGENTITY_HPP
#define PONGENTITY_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// be able to render sprites on the screen
class PongEntity : public sf::Sprite{
public:
	PongEntity() {
		this->texture = new sf::Texture();
	}

	void Load(std::string filename) {
		this->texture->loadFromFile("resources/" + filename);
		this->setTexture(*this->texture);
	}

	~PongEntity() {
		delete this->texture;
	}

	virtual void update() {
		this->move(this->velocity);
	}

	// Check for collision (experimental & awful)
	bool checkCollision(PongEntity* collision) {
		return this->getGlobalBounds().intersects(collision->getGlobalBounds());
	}
private:
	sf::Texture* texture;
protected:
	sf::Vector2f velocity;


};

#endif