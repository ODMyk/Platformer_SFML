#include "Entity.hpp"

Entity::Entity(sf::Vector2f hb): mHitbox(hb) {}

void Entity::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

void Entity::setVelocity(float x, float y) {
  mVelocity.x = x;
  mVelocity.y = y;
}

sf::Vector2f Entity::getVelocity() const { return mVelocity; }

sf::Vector2f Entity::getHitbox() const { return mHitbox; }

void Entity::updateCurrent(sf::Time timedelta) {
  move(mVelocity * timedelta.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity) { mVelocity += velocity; }
