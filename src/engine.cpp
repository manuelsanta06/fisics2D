#include <cstdlib>
#include <memory>
#include <cmath>
#include "engine.hpp"
#include "vect2.hpp"

constexpr float AIRF=0.5f;
constexpr float SLOP=0.02f;
constexpr float BAUMGARTE=0.8;

void world::pushObject(std::shared_ptr<PhysicObject> obj){
  objects.push_back(obj);
}

void world::runFrame(float deltaTime){
  for (auto& obj:objects){
    if(obj->invMass>0.0f){
      obj->forceAccumulator+=gravity*obj->mass;
    }
    obj->update(deltaTime);
    obj->vel*=std::pow(AIRF,deltaTime);
  }

  for(size_t i=0;i<objects.size();i++){
    for(size_t j=i+1;j<objects.size();j++){
      colisionsRouter(objects[i].get(),objects[j].get());
    }
  }
}

void world::colisionsRouter(PhysicObject* a,PhysicObject* b){
  if(a->invMass<=0&&b->invMass<=0)return;

  ShapeType typeA=a->getType();
  ShapeType typeB=b->getType();
  if(typeA==ShapeType::CIRCLE&&typeB==ShapeType::CIRCLE)
    resolveCollision(static_cast<Circle*>(a),static_cast<Circle*>(b));
  else if(typeA==ShapeType::CIRCLE&&typeB==ShapeType::AABB)
    resolveCollision(static_cast<Circle*>(a),static_cast<AABB*>(b));
  else if(typeA==ShapeType::AABB&&typeB==ShapeType::CIRCLE)
    resolveCollision(static_cast<AABB*>(a),static_cast<Circle*>(b));
  else if(typeA==ShapeType::AABB&&typeB==ShapeType::AABB)
    resolveCollision(static_cast<AABB*>(a),static_cast<AABB*>(b));
}

void world::resolveCollision(Circle* a,Circle* b){
  vector2 normal=a->pos-b->pos;
  float dist=normal.mag();
  if(dist!=0)normal/=dist;
  else normal={0.0f,-1.0f};

  float minDist=a->radius+b->radius;
  if(dist>minDist)return;

  float relVel=(a->vel-b->vel).dot(normal);
  if(relVel>0)return;

  vector2 j=(-(1+std::max(a->restitution,b->restitution))*relVel) / (a->invMass+b->invMass) *normal;
  vector2 separation=(minDist-dist)/(a->invMass+b->invMass)*normal*BAUMGARTE;

  a->vel+=j*a->invMass;
  b->vel-=j*b->invMass;

  a->pos+=separation*a->invMass;
  b->pos-=separation*b->invMass;
}

void world::resolveCollision(Circle* a,AABB* b){
  vector2 minP=b->getMin();
  vector2 maxP=b->getMax();
  vector2<float> closest={
    std::max(minP.x,std::min(a->pos.x,maxP.x)),
    std::max(minP.y,std::min(a->pos.y,maxP.y))
  };
  vector2<float> normal=a->pos-closest;
  float dist=(normal).mag();
  float penetration=0.0f;
  if(dist>a->radius)return;
  if(dist!=0){
    normal/=dist;
    penetration=a->radius-dist;
  }else{
    float distLeft=a->pos.x-minP.x;
    float distRight=maxP.x-a->pos.x;
    float distTop=a->pos.y-minP.y;
    float distBottom=maxP.y-a->pos.y;

    float minDistToEdge=distLeft;
    normal={-1.0f,0.0f};

    if(distRight<minDistToEdge){
      minDistToEdge=distRight;
      normal={1.0f,0.0f};
    }if(distTop<minDistToEdge){
      minDistToEdge=distTop;
      normal={0.0f,-1.0f};
    }if(distBottom<minDistToEdge){
      minDistToEdge=distBottom;
      normal={0.0f,1.0f};
    }
    penetration=a->radius+minDistToEdge;
  }

  float relVel=(a->vel-b->vel).dot(normal);
  if(relVel>0)return;

  vector2<float> j=(-(1+std::max(a->restitution,b->restitution))*relVel) / (a->invMass+b->invMass) *normal;
  vector2<float> separation=(penetration*BAUMGARTE)/(a->invMass+b->invMass) *normal;

  a->vel+=j*a->invMass;
  b->vel-=j*b->invMass;

  a->pos+=separation*a->invMass;
  b->pos-=separation*b->invMass;
}
void world::resolveCollision(AABB* a,Circle* b){
  return resolveCollision(b,a);
}

void world::resolveCollision(AABB* a,AABB* b){
  vector2<float> dist=a->pos-b->pos;
  vector2<float> overlap={
    (a->halfExtents.x+b->halfExtents.x)-std::abs(dist.x),
    (a->halfExtents.y+b->halfExtents.y)-std::abs(dist.y)
  };
  if(overlap.x<=0||overlap.y<=0)return;
  vector2<float> normal={0,0};
  float penetration=0;
  if(overlap.x<=overlap.y){  //horizontal
    normal.x=dist.x>=0?1.0f:-1.0f;
    penetration=overlap.x;
  }else{                     //vertical
    normal.y=dist.y>=0?1.0f:-1.0f;
    penetration=overlap.y;
  }

  float relVel=(a->vel-b->vel).dot(normal);
  if(relVel>0)return;

  vector2<float> j=(-(1+std::max(a->restitution,b->restitution))*relVel) / (a->invMass+b->invMass) *normal;
  vector2<float> separation=(penetration)*BAUMGARTE/(a->invMass+b->invMass)*normal;

  a->vel+=j*a->invMass;
  b->vel-=j*b->invMass;

  a->pos+=separation*a->invMass;
  b->pos-=separation*b->invMass;
}
