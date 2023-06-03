#include <SFML/Graphics/Rect.hpp>
#include <cstddef>
#include <iostream>
#include <memory>

#include "Headers/Avatar.hpp"
#include "Headers/Math.hpp"
#include "Headers/ResourceIdentifiers.hpp"
#include "SFML/System/Vector2.hpp"
#include "Headers/SpriteNode.hpp"
#include "Headers/World.hpp"

World::World(sf::RenderWindow &window)
    : mWindow(window), mWorldView(window.getDefaultView()),
      mWorldBounds(0.0f, 0.0f, 0.f, 0.f),
      mSpawnPosition(160.f, 160.f),
      mPlayerAvatar(nullptr) {
  loadTextures();
  buildScene();

  mWorldView.setCenter(
      mSpawnPosition); // explicitly changes the positin of the camera center to
                       // the player's absolute center
}

void World::loadTextures() {}

void World::buildScene() {
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

}

void World::draw() {
  mWindow.setView(mWorldView);
  mWindow.clear(sf::Color(0, 0, 0));
  mWindow.draw(mSceneGraph);
}

void World::update(sf::Time timedelta) {
  mPlayerAvatar->setVelocity(0.f, 0.f);

  while (!mCommandQueue.isEmpty()) {
    mSceneGraph.onCommand(mCommandQueue.pop(), timedelta);
  }

  mSceneGraph.update(timedelta);

  sf::Vector2f position = mPlayerAvatar->getPosition();
  mWorldView.setCenter(position);
}

CommandQueue &World::getCommandQueue() { return mCommandQueue; }
