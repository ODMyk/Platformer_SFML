#pragma once
#include "SceneNode.hpp"

class Entity: public SceneNode {
public:
	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float x, float y);
	void accelerate(sf::Vector2f velocity);
private:
	sf::Vector2f mVelocity;
	virtual void updateCurrent(sf::Time timedelta);
};

