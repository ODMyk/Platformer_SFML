#ifndef GAMESSTATE_HPP
#define GAMESSTATE_HPP

#include "Container.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GamesState : public State {
public:
  GamesState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  sf::Sprite mBackgroundSprite;
  GUI::Container mGUIContainer;
};

#endif

