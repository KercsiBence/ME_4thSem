#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, int *argv[]){

    srand(time(NULL));      
    int number = atoi(argv[1]);

    double time_spent = 0.0;
    int number_of_primes=0,i,counter;

    clock_t begin = clock();
    if (number==3)
    {
        number_of_primes=2;
    }else if (number==2)
    {
        number_of_primes=1;
    }else{
        number_of_primes=0;
        
        for(i=2;i<=number;i++){
            int divisible=0;
            for(counter=2;counter<=(int)i/2;counter++){

                if(i%counter==0){
                    divisible=1;
                    break;
                }
            }
            if (divisible==0)
            {
                printf("%d\n",i);
                number_of_primes++;
            }
            

        }
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%d",number_of_primes);
    printf("The elapsed time: %lf\n",time_spent);
    



}