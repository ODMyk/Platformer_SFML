#ifndef WORLD1_HPP
#define WORLD1_HPP

#include "World.hpp"

class World1: public World {
public:
  explicit World1(sf::RenderWindow &window);
  void update(sf::Time timedelta) override;
  void draw() override;

protected:
  void loadTextures() override;
  void buildScene() override;
};

#endif
