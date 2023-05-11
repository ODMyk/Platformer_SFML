#include <iostream>
#include "World1.hpp"
#include "SpriteNode.hpp"

World1::World1(sf::RenderWindow& window): World(window) {
  loadTextures();
  buildScene();
}

void World1::update(sf::Time delta) { World::update(delta); }

void World1::draw() { World::draw(); }

void World1::loadTextures() {
  mTextures.load(Textures::Background, "resources/img/Background.png");
  mTextures.load(Textures::Avatar, "resources/img/Player.jpg");
}

void World1::buildScene() {
  std::unique_ptr<Avatar> leader(new Avatar(Avatar::standard, mTextures));
  mPlayerAvatar = leader.get();
  mPlayerAvatar->setPosition(mSpawnPosition);
  mSceneLayers[Foreground]->attachChild(std::move(leader));

  sf::Texture &texture = mTextures.get(Textures::Background);
  mWorldBounds.width = texture.getSize().x;
  mWorldBounds.height = texture.getSize().y;
  sf::IntRect textureRect(mWorldBounds);

  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}
