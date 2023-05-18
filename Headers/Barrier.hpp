#ifndef BARRIER_HPP
#define BARRIER_HPP

#include "Entity.hpp"

class Avatar;

class Barrier: public Entity {
protected:
  virtual void onCollision(Avatar& pl, unsigned side);
};

#endif
