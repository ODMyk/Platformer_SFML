#pragma once

#include "ResourceHolder.hpp"

namespace sf {
	class Texture;
}

namespace Textures {
	enum ID {
		Grass,
		Avatar,
		Background,
	};
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
