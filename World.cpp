#include <SFML/Graphics/Rect.hpp>
#include <cstddef>
#include <iostream>
#include <memory>

#include "Avatar.hpp"
#include "Math.hpp"
#include "ResourceIdentifiers.hpp"
#include "SFML/System/Vector2.hpp"
#include "SpriteNode.hpp"
#include "World.hpp"

World::World(sf::RenderWindow &window)
    : mWindow(window), mWorldView(window.getDefaultView()),
      mWorldBounds(0.0f, 0.0f, 0.f, 0.f),
      mSpawnPosition(160.f, 180.f),
      mPlayerAvatar(nullptr), mPlayerSpeed(450.f) {
  loadTextures();
  buildScene();

  mWorldView.setCenter(
      mSpawnPosition); // explicitly changes the positin of the camera center to
                       // the player's absolute center
}

void World::loadTextures() {
  mTextures.load(Textures::Grass, "resources/img/Grass1.png");
  mTextures.load(Textures::Background, "resources/img/Background.png");
  mTextures.load(Textures::Avatar, "resources/img/Player.jpg");
  mTextures.load(Textures::ButtonNormal, "resources/img/Button0.png");
  mTextures.load(Textures::ButtonSelected, "resources/img/Button1.png");
  mTextures.load(Textures::ButtonPressed, "resources/img/Button2.png");
}

void World::buildScene() {
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  sf::Texture &texture = mTextures.get(Textures::Background);
  mWorldBounds.width = texture.getSize().x;
  mWorldBounds.height = texture.getSize().y;
  sf::IntRect textureRect(mWorldBounds);
  // texture.setRepeated(true); // uncomment if you have pattern-background

  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  std::unique_ptr<Avatar> leader(new Avatar(Avatar::standard, mTextures));
  mPlayerAvatar = leader.get();
  mPlayerAvatar->setPosition(mSpawnPosition);
  mSceneLayers[Foreground]->attachChild(std::move(leader));
}

void World::draw() {
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

void World::update(sf::Time timedelta) {
  // I am not sure, that player movement logic have to be there, in some time
  // this code functionality should be implemented with commands concept
  mPlayerAvatar->setVelocity(0.f, 0.f);
  sf::Vector2f absPlayerPos = mPlayerAvatar->getPosition();
  sf::Vector2f CameraTopLeft =
      sf::Vector2f(mWorldView.getCenter().x - mWorldView.getSize().x / 2.f,
                   mWorldView.getCenter().y - mWorldView.getSize().y / 2.f);
  sf::Vector2f relPlayerPos = sf::Vector2f(
      absPlayerPos.x - CameraTopLeft.x,
      absPlayerPos.y -
          CameraTopLeft.y); // position of the player center, relative to the
                            // Top Left angle of camera view

  // Camera movement with neutral area
  // replace this hardcoded values with some kind of formula
  //	if (relPlayerPos.x < 512 || relPlayerPos.x > 768) {
  //		mWorldView.move(movement.x * timedelta.asSeconds(), 0);
  //}
  // if (relPlayerPos.y < 299 || relPlayerPos.y > 469) {
  //	mWorldView.move(0, movement.y * timedelta.asSeconds());
  //}

  while (!mCommandQueue.isEmpty()) {
    mSceneGraph.onCommand(mCommandQueue.pop(), timedelta);
  }

  mSceneGraph.update(timedelta);

  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                           mWorldView.getSize());

  const float border = 32.f;
  sf::Vector2f position = mPlayerAvatar->getPosition();
  // position.x = std::max(mWorldBounds.left + border + viewBounds.width / 2,
  // position.x); position.x = std::min(mWorldBounds.left + mWorldBounds.width -
  // border - viewBounds.width / 2, position.x); position.y =
  // std::max(mWorldBounds.top + border + viewBounds.height / 2, position.y);
  // position.y = std::min(mWorldBounds.top + mWorldBounds.height - border -
  // viewBounds.height / 2, position.y);

  // mPlayerAvatar->setPosition(position);
  mWorldView.setCenter(position);
}

CommandQueue &World::getCommandQueue() { return mCommandQueue; }
