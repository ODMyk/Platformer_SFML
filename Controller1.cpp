#include <iostream>

#include "Headers/Avatar.hpp"
#include "Headers/Category.hpp"
#include "Headers/Command.hpp"
#include "Headers/Controller1.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>

struct BodyMover 
{
  BodyMover(float x, float y) : velocity(x, y) {}
  void operator()(Avatar &body, sf::Time dt) const 
  {
    body.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

Controller1::Controller1(Keybindings& binds): Controller(binds) 
{
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Left)] = MoveLeft;
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Right)] = MoveRight;

  initializeActions();

  for (auto &pair : mActionBinding) 
  {
    pair.second.category = Category::Player;
  }
}

void Controller1::initializeActions() 
{
  const float speed = 450.f;

  mActionBinding[MoveLeft].action =
      derivedAction<Avatar>(BodyMover(-speed, 0.f));
  mActionBinding[MoveRight].action =
      derivedAction<Avatar>(BodyMover(speed, 0.f));
}

void Controller1::handleRealtimeInput(CommandQueue &commands) 
{
  const float playerSpeed = 450.f;

  for (auto pair : mKeyBinding) 
  {
    if (sf::Keyboard::isKeyPressed(pair.first) &&
        isRealtimeAction(pair.second)) 
        {
				
				if (pair.second == MoveLeft || pair.second == MoveRight)
				{
      		commands.push(mActionBinding[pair.second]);
				}
    }
  }
}

void Controller1::handleEvent(const sf::Event &event, CommandQueue &commands) 
{
  if (event.type == sf::Event::KeyPressed) 
  {
    auto found = mKeyBinding.find(event.key.code);
    if (found != mKeyBinding.end() && !isRealtimeAction(found->second)) 
    {
      commands.push(mActionBinding[found->second]);
    }
  }
}

bool Controller1::isRealtimeAction(Action action) 
{
  switch (action) 
  {
    case MoveLeft:
    case MoveRight:
      return true;
    default:
      return false;
  }
}
