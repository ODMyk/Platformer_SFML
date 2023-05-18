#include "Barrier.hpp"
#include "Avatar.hpp"
#include "SFML/System/Vector2.hpp"

void Barrier::onCollision(Avatar& pl, unsigned side) {
  sf::Vector2f pos = getPosition();
  switch (side) {
    case 0: //left
      pl.setPosition(pos.x-getHitbox().x/2-pl.getHitbox().x/2, pl.getPosition().y);
      break;
    case 2: //right
      pl.setPosition(pos.x + getHitbox().x/2+pl.getHitbox().x/2, pl.getPosition().y);
      break;
    case 1: //top
      pl.setPosition(pl.getPosition().x, pos.y-getHitbox().y/2-pl.getHitbox().y/2);
      break;
    case 3: //bottom
      pl.setPosition(pl.getPosition().x, pos.y+getHitbox().y/2+pl.getHitbox().y/2);
  }
  sf::Vector2f vel = pl.getVelocity();
  if (side % 2) {
    vel.y = 0;
  } else {
    vel.x = 0;
  }
  pl.setVelocity(vel);
}
