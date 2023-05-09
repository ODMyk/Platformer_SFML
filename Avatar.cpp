#include "Avatar.hpp"

Textures::ID toTextureID(Avatar::Type type) {
  switch (type) {
  case Avatar::standard:
    return Textures::Avatar;
    break;
  default:
    throw "Not found";
    break;
  }
}

Avatar::Avatar(Type type, const TextureHolder &textures)
    : mType(type), mSprite() {
  mSprite.setTexture(textures.get(toTextureID(type)));
  sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Avatar::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  target.draw(mSprite, states);
}

unsigned int Avatar::getCategory() const {
  switch (mType) {
  case standard:
    return Category::Player;

  default:
    return Category::Scene;
  }
}
