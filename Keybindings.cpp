#include "Keybindings.hpp"

Keybindings::Keybindings() {
  keys.push_back(sf::Keyboard::W);
  keys.push_back(sf::Keyboard::S);
  keys.push_back(sf::Keyboard::A);
  keys.push_back(sf::Keyboard::D);
  keys.push_back(sf::Keyboard::E);
}

sf::Keyboard::Key Keybindings::getAssignedKey(const Events &event) const {
  return keys.at(event);
}

void Keybindings::assignKey(const sf::Keyboard::Key &key, const Events &event) {
  keys[event] = key;
}
