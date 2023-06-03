#ifndef SNAKE_HPP
#define SNAKE_HPP
#include "ResourceIdentifiers.hpp"
#include<SFML/System/Vector2.hpp>
#include<SFML/Graphics.hpp>


#include<iostream>
class Snake{
private:
    std::vector<sf::Vector2i>body;
    void upd();
public:
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void Eat();
    unsigned int getSize();
    sf::Vector2f getPosition(unsigned int ind);
    void add(unsigned int a, unsigned int b);
};
#endif // SNAKE_HPP
