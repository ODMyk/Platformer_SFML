#ifndef SNAKEWORLD_HPP
#define SNAKEWORLD_HPP
#include "World.hpp"
#include "Snake.hpp"
#include<iostream>
#include<fstream>
#include<vector>
#include<random>

class SnakeWorld: public World {
public:
  explicit SnakeWorld(sf::RenderWindow &window);
  void update(sf::Time timedelta);
  void draw();
  void loadLevel(std::string s);
  Snake snake;
  void handleEvent(const sf::Event &event);
  int random_number(int mod);
  void spawn_fruit();
  bool isGameOver();

protected:
  void loadTextures();
  void buildScene();
private:
    std::ifstream LevelMap;
    unsigned int levelWidth;
    unsigned int levelHeight;
    std::vector<std::vector<char> >A;
    bool GameOver=0;

    sf::Sprite Left;
    sf::Sprite Up;
    sf::Sprite Down;
    sf::Sprite Right;
    sf::Sprite Head;
};

#endif

