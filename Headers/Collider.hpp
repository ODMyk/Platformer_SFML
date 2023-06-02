#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "Entity.hpp"

class Avatar;

class Collider: public Entity {
private:
    sf::FloatRect body;
    sf::Vector2f center;
public:
    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f pos);
    void SetSizeX(float width);
    void SetSizeY(float height);
    float GetSizeX();
    float GetSizeY();
    sf::Vector2f GetCenter();
    Collider();
    ~Collider();
protected:
    virtual bool collision(Avatar& pl);
    virtual bool collision(sf::FloatRect rect);
};

class Barrier:public Collider{
    Barrier();
    ~Barrier();
protected:
    virtual bool collision(Avatar& pl);
};


#endif
