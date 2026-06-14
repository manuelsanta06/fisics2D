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
  void checkColisions(std::shared_ptr<PhysicObject> a,std::shared_ptr<PhysicObject> b);
};
