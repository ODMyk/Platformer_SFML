#include <iostream>

#include "Avatar.hpp"
#include "Category.hpp"
#include "Command.hpp"
#include "Player.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>

struct BodyMover {
  BodyMover(float x, float y) : velocity(x, y) {}
  void operator()(Avatar &body, sf::Time dt) const {
    body.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

Player::Player() {
  mKeyBinding[sf::Keyboard::W] = MoveUp;
  mKeyBinding[sf::Keyboard::S] = MoveDown;
  mKeyBinding[sf::Keyboard::A] = MoveLeft;
  mKeyBinding[sf::Keyboard::D] = MoveRight;
  mKeyBinding[sf::Keyboard::P] = PrintPosition;

  initializeActions();

  for (auto &pair : mActionBinding) {
    pair.second.category = Category::Player;
  }
}

void Player::initializeActions() {
  const float speed = 450.f;

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

void Player::handleRealtimeInput(CommandQueue &commands) {
  const float playerSpeed = 450.f;
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

  Command reduce;
  reduce.category = Category::Player;

  if (W && !S) {
    if (A && !D) {
      reduce.action = derivedAction<Avatar>(BodyMover(reducer, reducer));
      commands.push(reduce);
    } else if (!A && D) {
      reduce.action = derivedAction<Avatar>(BodyMover(-reducer, reducer));
      commands.push(reduce);
    }
  } else if (!W && S) {
    if (A && !D) {
      reduce.action = derivedAction<Avatar>(BodyMover(reducer, -reducer));
      commands.push(reduce);
    } else if (!A && D) {
      reduce.action = derivedAction<Avatar>(BodyMover(-reducer, -reducer));
      commands.push(reduce);
    }
  }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
  if (event.type == sf::Event::KeyPressed) {
    auto found = mKeyBinding.find(event.key.code);
    if (found != mKeyBinding.end() && !isRealtimeAction(found->second)) {
      commands.push(mActionBinding[found->second]);
    }
  }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
  for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();) {
    if (itr->second == action) {
      mKeyBinding.erase(itr++); // we have to use such approach because if we simply use increment in loop declaration, the iterator may broke and cause seg fault
    } else {
      ++itr;
    }
  }
  mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
  for (auto pair : mKeyBinding) {
    if (pair.second == action) {
      return pair.first;
    }
  }
  return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Action action) {
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
