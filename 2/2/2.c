#include <stdio.h>
#include <time.h>
#define SIZE 10
void unique(int * array);

int main(){

    srand(time(NULL));

    int array[SIZE];

    int i;
    double time_spent = 0.0;
    clock_t begin = clock();
    for (i = 0; i < SIZE; i++)
    {
        int new=0,num;
        do{
            num= rand() %(SIZE*3);
            new=1;
            int j;
            for (j = 0; j < i; j++)
            {
                if (array[j]==num)
                {
                    int random= rand() %2;
                }
                
            }
            
            
        } while (new==0);
        
        
        
        array[i]=num;

    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf",time_spent*1000);
    for (i = 0; i < SIZE; i++)
    {
        printf("%d\n",array[i]);
    }
    
    unique(&array[0]);

    return 0;
}
void unique(int * array){
    int uni=1,i,j;

    for (i = 0; i < SIZE-1; i++)
    {
        for (j = i+1; j < SIZE; j++)
        {
            if (array[i]==array[j])
            {
                uni=0;
            }
            
        }
        
    }
    if (uni==0)
    {
        printf("Nem egyedi");
    }
    else printf("Egyedi");
    


}