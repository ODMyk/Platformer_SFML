#ifndef SNAKEGAMESTATE_HPP
#define SNAKEGAMESTATE_HPP

#include<fstream>
#include<vector>
#include "State.hpp"
#include "SnakeWorld.hpp"
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "SnakeController.hpp"

class SnakeGameState : public State {
public:
  SnakeGameState(StateStack &stack, Context context);
  void draw();
  bool update(sf::Time dt);
  bool handleEvent(const sf::Event &event);

private:
  SnakeWorld mWorld;
  SnakeController mController;
};

#endif
