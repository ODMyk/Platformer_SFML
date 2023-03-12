#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity) {
	mVelocity = velocity;
}

void Entity::setVelocity(float x, float y) {
	mVelocity.x = x;
	mVelocity.y = y;
}

sf::Vector2f Entity::getVelocity() const {
	return mVelocity;
}

void Entity::updateCurrent(sf::Time timedelta) {
	move(mVelocity * timedelta.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity) {
	mVelocity += velocity;
}
