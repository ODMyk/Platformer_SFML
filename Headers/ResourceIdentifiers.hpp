#pragma once

#include "ResourceHolder.hpp"

namespace sf {
class Texture;
class Font;
} // namespace sf

namespace Textures {
enum ID {
  Grass,
  Avatar,
  Background,
  TitleScreen,
};
}

namespace Fonts {
enum ID {
  Main,
};
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
