#ifndef  WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

#include "Avatar.hpp"
#include "CommandQueue.hpp"
#include "SceneNode.hpp"

class World : private sf::NonCopyable {
public:
  explicit World(sf::RenderWindow &window);
  virtual void update(sf::Time timedelta);
  virtual void draw();
  CommandQueue &getCommandQueue();

protected:
  virtual void loadTextures();
  virtual void buildScene();

  enum Layer { Background, Foreground, UI, LayerCount };

  sf::RenderWindow &mWindow;
  sf::View mWorldView;
  TextureHolder mTextures;
  SceneNode mSceneGraph;
  std::array<SceneNode *, LayerCount> mSceneLayers;
  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  Avatar *mPlayerAvatar;
  CommandQueue mCommandQueue;
};

#endif
