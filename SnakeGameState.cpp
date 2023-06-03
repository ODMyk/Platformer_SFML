#include "Headers/SnakeGameState.hpp"

SnakeGameState::SnakeGameState(StateStack &stack, Context context)
    : State(stack, context), mWorld(*context.window),
      mController(*context.binds) {}

void SnakeGameState::draw() { mWorld.draw(); }

bool SnakeGameState::update(sf::Time dt) {
  mWorld.update(dt);
  return true;
}

bool SnakeGameState::handleEvent(const sf::Event &event) {

    if(mWorld.isGameOver())
        requestStackPush(States::SnakeGameOver); else
    if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause); else
    mWorld.handleEvent(event);
  return true;
}

