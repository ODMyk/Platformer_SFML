#ifndef SNAKEGAMEOVERSTATE_HPP
#define SNAKEGAMEOVERSTATE_HPP

#include "Container.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SnakeGameOverState : public State {
public:
  SnakeGameOverState(StateStack &stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);

private:
  sf::Sprite mBackgroundSprite;
  sf::Text mPausedText;
  GUI::Container mGUIContainer;
};

#endif

