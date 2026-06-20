#pragma once

#include <vector>
#include <memory>
#include "vect2.hpp"
#include "physicObjects.hpp"

const vector2<float> gravity(0.0f,980.0f);

class world{
  std::vector<std::shared_ptr<PhysicObject>> objects;

public:
  void pushObject(std::shared_ptr<PhysicObject> obj);

  void runFrame(float deltaTime);

private:
  void applyCollision(PhysicObject* a,PhysicObject* b,float penetration,vector2<float> normal);

  void collisionsRouter(PhysicObject* a,PhysicObject* b);

  void resolveCollision(Circle* a,Circle* b);
  void resolveCollision(Circle* a,AABB* b);
  void resolveCollision(AABB* a,Circle* b);
  void resolveCollision(AABB* a,AABB* b);
};
