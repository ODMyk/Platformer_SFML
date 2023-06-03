#include <iostream>
#include "Headers/Star.hpp"
#include "Headers/World2.hpp"
#include "Headers/SpriteNode.hpp"

World2::World2(sf::RenderWindow& window): World(window) 
{
  loadTextures();
  buildScene();
}

void World2::update(sf::Time delta) // Change this
{ 
    sf::Time dt = mClock.restart();
    mTimer += dt;
    
    if (mTimer > sf::seconds(5))
    {
      mTimer = sf::Time::Zero;
      std::unique_ptr<Star> star(new Star(mTextures.get(Textures::Star)));

      mSceneLayers[Foreground]->attachChild(std::move(star));
    }
    
    World::update(delta);
    
}

void World2::draw() { World::draw(); }

void World2::loadTextures() 
{
  mTextures.load(Textures::Background, "resources/img/bg1.jpg");
  mTextures.load(Textures::Avatar, "resources/img/Player.png");
  mTextures.load(Textures::Star, "resources/img/star.png");
  //mTextures.load(Textures::Foreground_, "resources/img/AllForNothing2.png");
}

void World2::buildScene() 
{
  std::unique_ptr<Avatar> leader(new Avatar(Avatar::standard, mTextures));
  mPlayerAvatar = leader.get();
  mPlayerAvatar->setPosition(mSpawnPosition);

  //sf::Texture &texture0 = mTextures.get(Textures::Foreground_);

  sf::Texture &texture = mTextures.get(Textures::Background);
  mWorldBounds.width = texture.getSize().x;
  mWorldBounds.height = texture.getSize().y;
  sf::IntRect textureRect(mWorldBounds);

  //std::unique_ptr<SpriteNode> foregroundSprite(new SpriteNode(texture0));
  //foregroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);

  mSceneLayers[Foreground]->attachChild(std::move(leader));

  //mSceneLayers[Foreground]->attachChild(std::move(foregroundSprite));



  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  std::cout<<mWorldBounds.left<<" "<<mWorldBounds.top<<"\n";
}
