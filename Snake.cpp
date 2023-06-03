#include "Headers/Snake.hpp"
#include "Headers/ResourceIdentifiers.hpp"
#include<iostream>
unsigned int Snake::getSize()
{
    return body.size();
}
void Snake::MoveUp()
{
    upd();
    if(body.size()>1)
        body[0]=body[1];
    body[0].y--;
}
void Snake::MoveDown()
{
    upd();
    if(body.size()>1)
        body[0]=body[1];
    body[0].y++;
}
void Snake::MoveRight()
{
    upd();
    if(body.size()>1)
        body[0]=body[1];
    body[0].x++;
}
void Snake::MoveLeft()
{
    upd();
    if(body.size()>1)
        body[0]=body[1];
    body[0].x--;
}
void Snake::Eat()
{
    body.push_back(body[0]);
}
sf::Vector2f Snake::getPosition(unsigned int ind)
{
    if(ind>=body.size()) {return {0, 0};}
    return {body[ind].x, body[ind].y};
}
void Snake::upd()
{
    for(int i=body.size()-1; i>0; i--)
    {
        std::swap(body[i], body[i-1]);
    }
}
void Snake::add(unsigned int a, unsigned int b)
{
    sf::Vector2i c = {a, b};
    body.push_back(c);
}
