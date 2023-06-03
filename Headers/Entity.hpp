#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
  sf::Vector2f getVelocity() const;
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float x, float y);
  void accelerate(sf::Vector2f velocity);

protected:
  virtual void updateCurrent(sf::Time timedelta);
  sf::Vector2f mVelocity;
};

#endif
