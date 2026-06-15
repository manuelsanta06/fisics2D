#include "raylib.h"
#include "src/engine.hpp"
#include "src/gameObjects.hpp"
#include "src/physicObjects.hpp"
#include "src/vect2.hpp"
#include <memory>

int currentWidth;
int currentHeight;

int main(){
  world engine;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800,800,"balls");
  SetTargetFPS(144);

  currentWidth=GetScreenWidth();
  currentHeight=GetScreenHeight();

  std::vector<GameObject> entities;

  GameObject gameHandler;
  Circle circleHalder;

  circleHalder.radius=30.0f;
  circleHalder.pos=vector2<float>(400.0f,100.0f);
  circleHalder.setMass(1.0f);
  gameHandler.physics=std::make_shared<Circle>(circleHalder);
  entities.push_back(gameHandler);
  engine.pushObject(gameHandler.physics);

  circleHalder.pos=vector2<float>(400.0f,200.0f);
  gameHandler.physics=std::make_shared<Circle>(circleHalder);
  entities.push_back(gameHandler);
  engine.pushObject(gameHandler.physics);

  circleHalder.pos=vector2<float>(400.5f,-3000.0f);
  gameHandler.physics=std::make_shared<Circle>(circleHalder);
  entities.push_back(gameHandler);
  engine.pushObject(gameHandler.physics);

  circleHalder.radius=10.0f;
  circleHalder.pos=vector2<float>(400.0f,760.0f);
  circleHalder.setMass(0.0f);
  gameHandler.physics=std::make_shared<Circle>(circleHalder);
  entities.push_back(gameHandler);
  engine.pushObject(gameHandler.physics);

  while(!WindowShouldClose()){
    if(IsWindowResized()){
      currentWidth=GetScreenWidth();
      currentHeight=GetScreenHeight();
    }

    Vector2 screenPos=GetWindowPosition();
    // Vector2 screenPos={0,0};

    engine.runFrame(GetFrameTime());

    BeginDrawing();
    ClearBackground(RAYWHITE); 
    
    for(auto& entidad:entities){
      if(entidad.physics){
        auto circulo=std::static_pointer_cast<Circle>(entidad.physics);
        DrawCircle(circulo->pos.x-screenPos.x,circulo->pos.y-screenPos.y,circulo->radius,MAROON);
      }
    }

    DrawText(TextFormat("Resolucion: %ix%i. FPS: %i",currentWidth,currentHeight,GetFPS()),10,10,18,BLACK);
    DrawLine(currentWidth/2,0,currentWidth/2,currentHeight,LIGHTGRAY);
    DrawLine(0,currentHeight/2,currentWidth,currentHeight/2,LIGHTGRAY);
    EndDrawing();
  }
  return 0;
}
