#include "Headers/Collider.hpp"
#include "Headers/Avatar.hpp"
#include "SFML/System/Vector2.hpp"
#include<iostream>
void Collider::SetPosition(sf::Vector2f pos)
{
    center.x+=pos.x-body.left;
    center.y+=pos.y-body.top;
    body.left=pos.x;
    body.top=pos.y;
}

void Collider::SetSizeX(float width)
{
    center.x+=width/2.f-body.width/2.f;
    body.width=width;
}
void Collider::SetSizeY(float height)
{
    center.y=center.y-height/2.f+body.height/2.f;
    body.height=height;
}
float Collider::GetSizeX() { return body.width; }
float Collider::GetSizeY() { return body.height; }
sf::Vector2f Collider::GetCenter(){ return center; }
sf::Vector2f Collider::GetPosition() {return sf::Vector2f(body.left, body.top);}
bool Collider::collision(Avatar& pl)
{
    sf::FloatRect bounds = pl.GetBounds();
    sf::Vector2f pl_center = {bounds.left+bounds.width/2.f, bounds.top-bounds.height/2.f};
    float intersection_x = abs(pl_center.x-GetCenter().x) - (GetSizeX()/2.f+bounds.width/2.f);
    float intersection_y = abs(pl_center.y-GetCenter().y) - (GetSizeY()/2.f+bounds.height/2.f);
    if(intersection_x<0 || intersection_y<0)
    {
        std::cout<<"Collision\n";
        return true;
    }
    std::cout<<"No collision\n";
    return false;
}
bool Collider::collision(sf::FloatRect rect)
{
    sf::Vector2f rect_center = {rect.left+rect.width/2.f, rect.top-rect.height/2.f};
    float intersection_x = abs(rect_center.x-GetCenter().x) - (GetSizeX()/2.f+rect.width/2.f);
    float intersection_y = abs(rect_center.y-GetCenter().y) - (GetSizeY()/2.f+rect.height/2.f);
    if(intersection_x<0 || intersection_y<0)
    {
        std::cout<<"Collision\n";
        return true;
    }
    std::cout<<"No collision\n";
    return false;
}

bool Barrier::collision(Avatar& pl)
{
    sf::FloatRect bounds = pl.GetBounds();
    sf::Vector2f pl_center = {bounds.left+bounds.width/2.f, bounds.top-bounds.height/2.f};
    float intersection_x = abs(pl_center.x-GetCenter().x) - (GetSizeX()/2.f+bounds.width/2.f);
    float intersection_y = abs(pl_center.y-GetCenter().y) - (GetSizeY()/2.f+bounds.height/2.f);
    if(intersection_x<0) {pl.accelerate({-2.f*pl.getVelocity().x, 0});}
    if(intersection_y<0) {pl.accelerate({0, -2.f*pl.getVelocity().y});}
    if(intersection_x<0 || intersection_y<0)
    {
        std::cout<<"Collision\n";
        return true;
    }
    std::cout<<"No collision\n";
    return false;
}
