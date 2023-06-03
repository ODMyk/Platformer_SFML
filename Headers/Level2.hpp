#ifndef LEVEL2_HPP
#define LEVEL2_HPP

#include "State.hpp"
#include "World2.hpp"
#include "Controller1.hpp"

class Level2 : public State {
public:
  Level2(StateStack &stack, Context context);
  void draw();
  bool update(sf::Time dt);
  bool handleEvent(const sf::Event &event);

private:
  World2 mWorld;
  Controller1 mController;
};

#endif
