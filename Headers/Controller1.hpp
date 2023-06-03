#ifndef CONTROLLER1_HPP
#define CONTROLLER1_HPP

#include <SFML/Window.hpp>
#include <map>

#include "CommandQueue.hpp"
#include "Keybindings.hpp"
#include "Controller.hpp"


class Controller1 : public Controller {
public:
  Controller1(Keybindings& binds);
  void handleEvent(const sf::Event &event, CommandQueue &commands) override;
  void handleRealtimeInput(CommandQueue &commands) override;

protected:
  bool isRealtimeAction(Controller::Action action) override;
  void initializeActions() override;
};

#endif
