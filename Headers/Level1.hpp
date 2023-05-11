#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "State.hpp"
#include "World1.hpp"
#include "Controller.hpp"

class Level1 : public State {
public:
  Level1(StateStack &stack, Context context);
  void draw();
  bool update(sf::Time dt);
  bool handleEvent(const sf::Event &event);

private:
  World1 mWorld;
  Controller mController;
};

#endif
