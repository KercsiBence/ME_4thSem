#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, int *argv[]){

    srand(time(NULL));      
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int flag=0;

    if( argc > 3 ) {
        printf("Too many arguments supplied.\n");
    }
    else if (argc < 3){
        printf("Too few arguments.\n");
    }
    printf("A min: %d, a max: %d\n",min,max);

    int i;
    char answer;
    do{
        
            int x= (rand() %(max-min)) + min;
            int y= (rand() %(max-min)) + min;
            int goodsum=0, sum;
            double time_spent = 0.0;
            clock_t begin = clock();
            printf("Kerlek add ossze a 2 szamot: %d es %d\n",x,y);
            do{
                
                printf("Your answer: ");
                scanf("%d",&sum);
                if(sum==x+y){
                    goodsum=1;
                }

            }while(goodsum==0);

            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            printf("The elapsed time: %lf\n",time_spent);

            printf("Wanna continue? (q=quit) :");
            scanf(" %c",&answer);
            if (answer == 'Q' || answer == 'q')
            {
                flag=1;
            }
            
        
    }while (flag==0);
     
     printf("Thanks for playing");



    return 0;
}