#pragma once

#include <memory>
#include "physicObjects.hpp"

class GameObject{
public:
  std::shared_ptr<PhysicObject> physics;
  
  // std::shared_ptr<RenderObject> sprite;

  void update(float dt){
    // if(physics&&sprite){
    //   sprite->setPosition(physics->pos);
    //   sprite->setRotation(physics->angle);
    // }
  }
};
