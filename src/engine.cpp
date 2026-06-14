#include <memory>
#include "engine.hpp"



void world::pushObject(std::shared_ptr<PhysicObject> obj){
  objects.push_back(obj);
}

void world::runFrame(float deltaTime){
  for (auto& obj:objects){
    if(obj->invMass>0.0f){
      obj->forceAccumulator+=gravity*obj->mass;
    }
    obj->update(deltaTime);
    obj->vel*=0.99f;
  }

  for(size_t i=0;i<objects.size();i++){
    for(size_t j=i+1;j<objects.size();j++){
      checkColisions(objects[i], objects[j]);
    }
  }
}

void world::checkColisions(std::shared_ptr<PhysicObject> a,std::shared_ptr<PhysicObject> b){
}
