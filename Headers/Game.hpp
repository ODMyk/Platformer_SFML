#ifndef GAME_HPP
#define GAME_HPP

#include "Avatar.hpp"
#include "Player.hpp"
#include "World.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game();
  void run();

private:
  void processInput();
  void update(sf::Time timedelta);
  void updateStatistics(sf::Time timedelta);
  void render();

private:
  Player mPlayer;
  bool mIsPaused;

  sf::RenderWindow mWindow;
  World mWorld;
  const sf::Time FrameTime;

  sf::Time statTime;
  int framesCount;
  sf::Font mFont;
  sf::Text textFPS;
};

#endif
