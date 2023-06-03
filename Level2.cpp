#include "Headers/Level2.hpp"

Level2::Level2(StateStack &stack, Context context)
    : State(stack, context), mWorld(*context.window),
      mController(*context.binds) {}

void Level2::draw() { mWorld.draw(); }

bool Level2::update(sf::Time dt) 
{
  mWorld.update(dt);

  CommandQueue &commands = mWorld.getCommandQueue();
  mController.handleRealtimeInput(commands);

  return true;
}

bool Level2::handleEvent(const sf::Event &event) 
{
  CommandQueue &commands = mWorld.getCommandQueue();
  mController.handleEvent(event, commands);

  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);

  return true;
}
