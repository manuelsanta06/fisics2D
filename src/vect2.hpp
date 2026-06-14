#pragma once

#include <cmath>

template<class T>
struct vector2{
  T x,y;
  
  vector2(T X,T Y):x(X),y(Y){}
  vector2():x(0),y(0){}


  T& operator[](int index){return (index==0)?x:y;}
  const T& operator[](int index)const{return (index==0)?x:y;}


  vector2& operator+=(const vector2& other){
    this->x+=other.x;
    this->y+=other.y;
    return *this;
  }
  vector2& operator-=(const vector2& other){
    this->x-=other.x;
    this->y-=other.y;
    return *this;
  }
  vector2& operator*=(const vector2& other){
    this->x*=other.x;
    this->y*=other.y;
    return *this;
  }
  vector2& operator/=(const vector2& other){
    this->x/=other.x;
    this->y/=other.y;
    return *this;
  }

  vector2& operator*=(T scalar){
    this->x*=scalar;
    this->y*=scalar;
    return *this;
  }
  vector2& operator/=(T scalar){
    this->x/=scalar;
    this->y/=scalar;
    return *this;
  }


  vector2 operator*(T scalar)const{
    return vector2(*this)*=scalar;
  }
  friend vector2 operator*(T scalar, const vector2& vec){
    return vec*scalar;
  }
  vector2 operator/(T scalar)const{
    return vector2(*this)/=scalar;
  }

  vector2 operator+(const vector2& other)const{
    return vector2(*this)+=other;
  }
  vector2 operator-(const vector2& other)const{
    return vector2(*this)-=other;
  }
  vector2 operator*(const vector2& other)const{
    return vector2(*this)*=other;
  }
  vector2 operator/(const vector2& other)const{
    return vector2(*this)/=other;
  }


  vector2 operator-()const{
    return vector2(-x,-y);
  }


  //utilities
  T dot(const vector2& other)const{
    return x*other.x+y*other.y;
  }

  T magSq()const{
    return x*x+y*y;
  }

  T mag()const{
    return std::sqrt(magSq());
  }

  vector2 perp() const{
    return vector2(-y,x);
  }
};
