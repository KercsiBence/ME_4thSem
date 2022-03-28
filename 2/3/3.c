#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
double random_in_range(double min, double max);
void monotonius(double *array);
void monotoniusR(double *array, int num);

int main(){
    srand(time(NULL));
    int i;
    double array[SIZE];

    for (i = 0; i < SIZE; i++)
    {
        if (i>0)
        {
            do{
                array[i]=random_in_range(0,(SIZE/2));
                if (array[i]==5.000000 && i!=SIZE-1)
                {
                    printf("Generated the bigest number so the program shut down");
                    exit(-1);
                }
                
            }while(array[i]<=array[i-1]);
        }else array[i]=random_in_range(0,(SIZE/2));
        
        printf("%lf\n",array[i]);
    }
    
    monotonius(&array[0]);
    monotoniusR(&array[0],SIZE-1);

    return 0;
}
double random_in_range(double min, double max){

    double random= ( (double ) rand () ) / RAND_MAX;
    double range= (max-min)*random;
    double number= min+range;
    return number;
}
void monotonius(double *array){
    int outcome=1,i;

    for (i = 1; i < SIZE; i++)
    {
        if (array[i]<array[i-1])
        {
            outcome=0;
        }
        
    }
    if (outcome==0)
    {
        printf("Not true");
    }else printf("True");
}
void monotoniusR(double *array, int num){

    if (num>0)
    {
        if(array[num]>array[num-1]){
            monotoniusR(array,num-1);
        }else {
            printf("Not true");
        }
    }
}
