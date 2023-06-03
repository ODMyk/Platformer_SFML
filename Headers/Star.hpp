#ifndef STAR_HPP
#define STAR_HPP

#include "Entity.hpp"

class Star : public Entity
{
    private:
        sf::Sprite mSprite;

    protected:
        void updateCurrent(sf::Time timedelta) override;

    public:
        Star(sf::Texture &texture);
        Star(Star&&);
        void drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const;
};

#endif