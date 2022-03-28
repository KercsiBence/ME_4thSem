#include <time.h>
#include <stdlib.h>

int main (){
    srand(time(NULL));   

    int i;
    for (i=0; i<20; i++){
        printf("%d\n ",(rand() %500) + 500);
    }
    printf("Here comes the floats: ");
    for (i=0; i<20; i++){
        
         printf("%f\n", ((float)rand()/(float)(RAND_MAX)) * 5.0);
    }

return 0;
}
