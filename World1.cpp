#include <iostream>
#include "Headers/World1.hpp"
#include "Headers/SpriteNode.hpp"

World1::World1(sf::RenderWindow& window): World(window) {
  loadTextures();
  buildScene();
}

void World1::update(sf::Time delta) { World::update(delta); }

void World1::draw() { World::draw(); }

void World1::loadTextures() {
  mTextures.load(Textures::Background, "resources/img/Background.png");
  mTextures.load(Textures::Avatar, "resources/img/Player.png");
  mTextures.load(Textures::Foreground_, "resources/img/AllForNothing2.png");
}

void World1::buildScene() {
  std::unique_ptr<Avatar> leader(new Avatar(Avatar::standard, mTextures));
  mPlayerAvatar = leader.get();
  mPlayerAvatar->setPosition(mSpawnPosition);

  sf::Texture &texture0 = mTextures.get(Textures::Foreground_);

  sf::Texture &texture = mTextures.get(Textures::Background);
  mWorldBounds.width = texture.getSize().x;
  mWorldBounds.height = texture.getSize().y;
  sf::IntRect textureRect(mWorldBounds);

  std::unique_ptr<SpriteNode> foregroundSprite(new SpriteNode(texture0));
  foregroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);

  mSceneLayers[Foreground]->attachChild(std::move(leader));

  mSceneLayers[Foreground]->attachChild(std::move(foregroundSprite));



  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  std::cout<<mWorldBounds.left<<" "<<mWorldBounds.top<<"\n";
}
