#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
  Entity(sf::Vector2f);
  sf::Vector2f getVelocity() const;
  sf::Vector2f getHitbox() const;
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float x, float y);
  void accelerate(sf::Vector2f velocity);

private:
  sf::Vector2f mVelocity;
  sf::Vector2f mHitbox;
  virtual void updateCurrent(sf::Time timedelta);
};

#endif
