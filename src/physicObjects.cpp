#include "physicObjects.hpp"

void PhysicObject::update(float dt){
  vector2<float> acceleration=forceAccumulator*invMass;

  vel+=acceleration*dt;
  pos+=vel*dt;

  forceAccumulator=vector2<float>(0,0);
}
