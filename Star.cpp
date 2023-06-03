#include "Headers/Star.hpp"
#include "cstdlib"
#include "iostream"

Star::Star(sf::Texture &texture)
{
    setPosition(rand() % 300, 0);
    mSprite.setTexture(texture);
    std::cout << "I am spawned!" << std::endl;
}

Star::Star(Star &&other)
{
    mSprite = other.mSprite;
    setPosition(other.getPosition().x, other.getPosition().y);
}

void Star::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const 
{
  target.draw(mSprite, states);
}

void Star::updateCurrent(sf::Time timedelta)
{
    setVelocity(0, 30.1);
    Entity::updateCurrent(timedelta);
}