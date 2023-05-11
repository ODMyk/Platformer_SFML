#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Window.hpp>
#include <map>

#include "CommandQueue.hpp"
#include "Keybindings.hpp"


class Controller {
public:
  enum Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    PrintPosition,
    ActionCount,
  };

  Controller(Keybindings& binds);
  virtual void handleEvent(const sf::Event &event, CommandQueue &commands);
  virtual void handleRealtimeInput(CommandQueue &commands);
  sf::Keyboard::Key getAssignedKey(Action action) const;

protected:
  Keybindings& mBinds;
  virtual bool isRealtimeAction(Action action);
  virtual void initializeActions();
  std::map<sf::Keyboard::Key, Action> mKeyBinding;
  std::map<Action, Command> mActionBinding;
};

#endif
