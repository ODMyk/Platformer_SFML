#include <iostream>

#include "Headers/Avatar.hpp"
#include "Headers/Category.hpp"
#include "Headers/Command.hpp"
#include "Headers/SnakeController.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>

struct BodyMover {
  BodyMover(float x, float y) : velocity(x, y) {}
  void operator()(Avatar &body, sf::Time dt) const {
    body.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

SnakeController::SnakeController(Keybindings& binds): mBinds(binds) {
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Up)] = MoveUp;
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Down)] = MoveDown;
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Left)] = MoveLeft;
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Right)] = MoveRight;
  mKeyBinding[mBinds.getAssignedKey(Keybindings::Events::Interact)] = PrintPosition;

  initializeActions();

  for (auto &pair : mActionBinding) {
    pair.second.category = Category::Player;
  }
}

void SnakeController::initializeActions() {
  const float speed = 100;

  mActionBinding[MoveUp].action = derivedAction<Avatar>(BodyMover(0.f, -speed));
  mActionBinding[MoveDown].action =
      derivedAction<Avatar>(BodyMover(0.f, speed));
  mActionBinding[MoveLeft].action =
      derivedAction<Avatar>(BodyMover(-speed, 0.f));
  mActionBinding[MoveRight].action =
      derivedAction<Avatar>(BodyMover(speed, 0.f));
  mActionBinding[PrintPosition].action = [](SceneNode &node, sf::Time) {
    std::cout << node.getPosition().x << " " << node.getPosition().y
              << std::endl;
  };
}

void SnakeController::handleRealtimeInput(CommandQueue &commands) {
  const float playerSpeed = 100.f;
  const float reducer = playerSpeed * (1.f - 1.f / sqrt(2.f));
  std::map<Action, bool> actions;
  actions[MoveLeft] = false;
  actions[MoveRight] = false;
  actions[MoveDown] = false;
  actions[MoveUp] = false;

  for (auto pair : mKeyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) &&
        isRealtimeAction(pair.second)) {
      commands.push(mActionBinding[pair.second]);
      actions[pair.second] = true;
    }
  }

  bool W = actions[Action::MoveUp];
  bool S = actions[Action::MoveDown];
  bool A = actions[Action::MoveLeft];
  bool D = actions[Action::MoveRight];

//  Command reduce;
//  reduce.category = Category::Player;
}

void SnakeController::handleEvent(const sf::Event &event, CommandQueue &commands) {
  if (event.type == sf::Event::KeyPressed) {
    auto found = mKeyBinding.find(event.key.code);
    if (found != mKeyBinding.end() && !isRealtimeAction(found->second)) {
      commands.push(mActionBinding[found->second]);
    }
  }
}

sf::Keyboard::Key SnakeController::getAssignedKey(Action action) const {
  for (auto pair : mKeyBinding) {
    if (pair.second == action) {
      return pair.first;
    }
  }
  return sf::Keyboard::Unknown;
}

bool SnakeController::isRealtimeAction(Action action) {
  switch (action) {
  case MoveUp:
  case MoveDown:
  case MoveLeft:
  case MoveRight:
    return true;
  default:
    return false;
  }
}

