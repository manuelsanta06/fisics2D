#pragma once
#include "vect2.hpp"

enum class ShapeType{
  CIRCLE,
  AABB,
  POLYGON
};

class PhysicObject{
public:
  virtual ~PhysicObject()=default;
  virtual void update(float dt);
  virtual ShapeType getType()const=0;

  vector2<float> pos;
  vector2<float> vel;
  vector2<float> forceAccumulator;

  float angle=0.0f;
  float angularVel=0.0f;
  float torque=0.0f;

  float mass=1.0f;
  float invMass=1.0f;

  void setMass(float newMass){
    mass=newMass;
    invMass=newMass>0.0f?1/mass:0.0f;
  }
};

class Circle:public PhysicObject{
public:
  float radius;
  // void update(float dt)override;
  ShapeType getType()const override{return ShapeType::CIRCLE;}
};

