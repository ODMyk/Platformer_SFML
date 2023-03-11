#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Avatar: public Entity {
public:
	enum Type {
		standard,
	};
	explicit Avatar(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	unsigned int getCategory() const override;
private:
	Type mType;
	sf::Sprite mSprite;
};
