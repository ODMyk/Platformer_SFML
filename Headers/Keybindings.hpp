#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include <vector>
#include <SFML/Window/Keyboard.hpp>

class Keybindings {
public:
enum Events {
  Up,
  Down,
  Left,
  Right,
  Interact,
  KeyCount,
};

  Keybindings();
  sf::Keyboard::Key getAssignedKey(const Events &event) const;
  void assignKey(const sf::Keyboard::Key &key, const Events &event);

private:
std::vector<sf::Keyboard::Key> keys;
};

#endif
