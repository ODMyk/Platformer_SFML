#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Keybindings.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class SettingsState : public State {
public:
  SettingsState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  void updateLabels();
  void addButtonLabel(Keybindings::Events action, float y, const std::string &text,
                      Context context);

private:
  sf::Sprite mBackgroundSprite;
  GUI::Container mGUIContainer;
  std::array<GUI::Button::Ptr, Keybindings::KeyCount> mBindingButtons;
  std::array<GUI::Label::Ptr, Keybindings::KeyCount> mBindingLabels;
};

#endif
