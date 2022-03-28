#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

    srand(time(NULL)); 
    FILE *fp;
    fp=fopen(argv[1],"w");

    double time_spent = 0.0;
    clock_t begin = clock();
    int max = atoi(argv[2]);
    int i;
    for(i=0;i<max;i++){
        int num= rand() %max;
        fprintf(fp,"%d\n",num);
    }
    fclose(fp);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf",time_spent);
    return 0;
}