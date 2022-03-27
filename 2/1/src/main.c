#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

struct Coordinate{
  int x1,x2,y1,y2;
};
struct RGB{
  int r,g,b;
};
struct Line{
  struct Coordinate point;
  struct RGB rgb;
  int in_progress;
}line;


int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer* renderer;
  int i;

  struct RGB rgbs[5];
  rgbs[0].r=255;
  rgbs[0].g=0;
  rgbs[0].b=0;
  rgbs[1].r=0;
  rgbs[1].g=255;
  rgbs[1].b=0;
  rgbs[2].r=0;
  rgbs[2].g=0;
  rgbs[2].b=255;
  rgbs[3].r=255;
  rgbs[3].g=255;
  rgbs[3].b=255;
  rgbs[4].r=0;
  rgbs[4].g=0;
  rgbs[4].b=0;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Bence's first SDL program!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    1400, 800, 0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

int counter=0;
for (int g = 0; g <2 ; g++)
{
  for (int j = 0; j < 2; j++)
  {
    
    for (int i = 1350-j*50; i < 1400-j*50; i++)
    {
    
      SDL_SetRenderDrawColor(renderer, rgbs[counter].r, rgbs[counter].g, rgbs[counter].b, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(renderer,i,750-g*50,i,800-g*50);
    
    }
    counter++;
  }
  
}



  int x, y;
  Uint32 buttons;
  need_run = true;
  while (need_run) {
    while (SDL_PollEvent(&event)!=0) {


      if (event.type==SDL_QUIT)
      {
        need_run=false;
      }
      else if(event.type==SDL_MOUSEBUTTONDOWN){
        if(event.button.button==SDL_BUTTON_LEFT){
              SDL_PumpEvents();
              buttons = SDL_GetMouseState(&x, &y);
          if (x>=1350){
            if (y>=750)
            {
              rgbs[4].r=255;
              rgbs[4].g=0;
              rgbs[4].b=0;
              printf("Red: %d, Green: %d, Blue: %d",rgbs[4].r,rgbs[4].g,rgbs[4].b); sleep(1);
            }else if(y>700){
              rgbs[4].r=0;
              rgbs[4].g=0;
              rgbs[4].b=255;
              printf("Red: %d, Green: %d, Blue: %d",rgbs[4].r,rgbs[4].g,rgbs[4].b); sleep(1);
            }
            
          }else if(x>1300){
            if (y>=750)
            {
              rgbs[4].r=0;
              rgbs[4].g=255;
              rgbs[4].b=0;
              printf("Red: %d, Green: %d, Blue: %d",rgbs[4].r,rgbs[4].g,rgbs[4].b); sleep(1);
            }else if(y>700){
              rgbs[4].r=255;
              rgbs[4].g=255;
              rgbs[4].b=255;
              printf("Red: %d, Green: %d, Blue: %d",rgbs[4].r,rgbs[4].g,rgbs[4].b); sleep(1);
            }
          }
          else{
            if (line.in_progress==0)
            {
              line.point.x1=x;
              line.point.y1=y;
              line.in_progress=1;
            }else{
              line.point.x2=x;
              line.point.y2=y;
              line.in_progress=0;
              SDL_SetRenderDrawColor(renderer,rgbs[4].r, rgbs[4].g, rgbs[4].b, SDL_ALPHA_OPAQUE);
              SDL_RenderDrawLine(renderer,line.point.x1,line.point.y1,line.point.x2,line.point.y2);
            }
              
            }

        }else if (event.button.button==SDL_BUTTON_RIGHT){
          need_run = false;
          break;
        }
      }
        
    }    
    SDL_RenderPresent(renderer);
    
 }
sleep(10);


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
