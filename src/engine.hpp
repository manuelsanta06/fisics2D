#ifndef ENGINED
#define ENGINED

#include <vector>
#include <memory>
#include "vect2.hpp"

class FisicObject{
public:
  virtual ~FisicObject()=default;
  virtual void update(float dt)=0;

  vector2<float> pos;
  vector2<float> vel;
  vector2<float> rotVel;
  float mas;
};

class Circle:public FisicObject{
public:
  float radius;
  void update(float dt)override;
};

class world{
  std::vector<std::shared_ptr<FisicObject>> objetos;

public:
  void pushObject(std::shared_ptr<FisicObject> obj);

  void runFrame(float deltaTime);

private:
  void chequearColision(std::shared_ptr<FisicObject> a,std::shared_ptr<FisicObject> b);
};


#endif
