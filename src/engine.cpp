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
      colisionsRouter(objects[i],objects[j]);
    }
  }
}

void world::colisionsRouter(std::shared_ptr<PhysicObject> a,std::shared_ptr<PhysicObject> b){
  ShapeType typeA=a->getType();
  ShapeType typeB=b->getType();
  if(typeA==ShapeType::CIRCLE&&typeB==ShapeType::CIRCLE)
    resolveCircleCircle(std::static_pointer_cast<Circle>(a),std::static_pointer_cast<Circle>(b));
}

void world::resolveCircleCircle(std::shared_ptr<Circle> a,std::shared_ptr<Circle> b){
  if(a->invMass<=0&&b->invMass<=0)return;

  vector2 normal=a->pos-b->pos;
  float dist=normal.mag();
  if(dist!=0)normal/=dist; //secure normalizing
  else normal={0.0f,-1.0f};

  float minDist=a->radius+b->radius;
  if(dist>minDist)return;

  float acercVel=(a->vel-b->vel).dot(normal);
  if(acercVel>0)return;

  vector2 j=(-(1+0.8)*acercVel) / (a->invMass+b->invMass) *normal;
  vector2 separation=(minDist-dist)/(a->invMass+b->invMass)*normal;

  a->vel+=j*a->invMass;
  b->vel-=j*b->invMass;

  a->pos+=separation*a->invMass;
  b->pos-=separation*b->invMass;
}
