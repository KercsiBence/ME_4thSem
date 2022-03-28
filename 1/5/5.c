#include <time.h>
#include <stdlib.h>

int main(int argc, int *argv[]){

    srand(time(NULL));      
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    if( argc > 3 ) {
        printf("Too many arguments supplied.\n");
    }
    else if (argc < 3){
        printf("Too few arguments.\n");
    }
    printf("%d %d\n",min,max);
    int i;
     for (i=0; i<20; i++){
        int r= (rand() %(max-min)) + min;
        printf("%d\n ",r);
    }



    return 0;
}