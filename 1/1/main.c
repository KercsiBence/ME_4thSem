#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
void set_size (int *x,int *y,int *z);
int calc_volume(int x, int y, int z);
int calc_surface(int x, int y, int z);
void has_square_side(int x, int y, int z);

struct Brick {
  int x;
  int y;
  int z;
  int volume;
  int surface;
} brick;

int main(int argc, char* argv[])
{ 
  set_size(&brick.x,&brick.y,&brick.z);
  brick.volume=calc_volume(brick.x,brick.y,brick.z);
  brick.surface=calc_surface(brick.x,brick.y,brick.z);
  has_square_side(brick.x,brick.y,brick.z);

  printf("The volume is: %d\nThe surface is: %d",brick.volume, brick.surface);
  sleep(5);
  return 0;
}

void set_size (int *x,int *y,int *z) {
  int ok=0;
    printf("Please type the length of each sides!\n"); 
    if (scanf("%d,%d,%d",x,y,z)!=3)
    {
      printf("Wrong data!");
      exit(-1);
    }

  
}
int calc_volume(int x, int y, int z){
  return x*y*z;
}
int calc_surface(int x, int y, int z){
  return 2*x*y+2*x*z+2*y*z;
}
void has_square_side(int x, int y, int z){
  if (x==y)
  {
    if (x==z)
    {
      printf("It's a cube!\n");
    }
    else{
      printf("It's not a cube, but x is equal to y!\n");
    }
  }else if(y==z){
    printf("It's not a cube, but y is equal to z!\n");
  }else if(x==z){
    printf("It's not a cube, but x is equal to z!\n");
  }else{
    printf("None of the sizes are equal!\n");
  }
}
