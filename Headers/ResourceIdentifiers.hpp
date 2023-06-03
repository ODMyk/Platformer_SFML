#pragma once

#include "ResourceHolder.hpp"

namespace sf {
class Texture;
class Font;
} // namespace sf

namespace Textures {
enum ID {
  Avatar,
  Background,
  TitleScreen,
  ButtonNormal,
  ButtonPressed,
  ButtonSelected,
  Foreground_,
  SnakeHead,
  SnakeTailUp,
  SnakeTailDown,
  SnakeTailRight,
  SnakeTailLeft
};
}

namespace Fonts {
enum ID {
  Main,
};
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
