#ifndef WORLD2_HPP
#define WORLD2_HPP

#include "World.hpp"

class World2: public World 
{
public:
  explicit World2(sf::RenderWindow &window);
  void update(sf::Time timedelta) override;
  void draw() override;

protected:
  void loadTextures() override;
  void buildScene() override;
  sf::Clock mClock;
  sf::Time mTimer;
};

#endif
