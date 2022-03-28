#include <stdio.h>
#include <time.h>

int fileLines(char *filename);
void fileNumbers(char *filename,int* intArray,int linesNumber);
void sumCalc(int *sum, int* intArray, int length);
void minCalc(int *sum, int* intArray, int length);
void maxCalc(int *sum, int* intArray, int length);
void sumCalcR(int *sumR, int* intArray, int length);
void minCalcR(int *minR, int* intArray, int length);
void maxCalcR(int *minR, int* intArray, int length);

int main(){

    int lines=0;
    char *filename="test.txt";

    lines=fileLines(filename);
    int intArray[lines];
    fileNumbers(filename,&intArray[0],lines);

    int sum=0,sumR=0,min=intArray[0],max=intArray[0],minR=intArray[0],maxR=intArray[0];
    clock_t start, end;
    double time_used;
     
    start = clock();
    sumCalc(&sum,&intArray[0],lines);
    minCalc(&min,&intArray[0],lines);
    maxCalc(&max,&intArray[0],lines);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sum: %d, Min: %d, Max: %d, Time required: %lf\n",sum,min,max,time_used);

    start = clock();
    sumCalcR(&sumR,&intArray[0],lines-1);
    minCalcR(&minR,&intArray[0],lines-1);
    maxCalcR(&maxR,&intArray[0],lines-1);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sum: %d, Min: %d, Max: %d, Time required: %lf\n",sumR,minR,maxR,time_used);
    
    return 0;
}

int fileLines(char *filename){
    FILE *fp=fopen(filename,"r");
    char ch;
    int lines=0;


    if (fp==NULL)
    {
        printf("Hiba a filehoz valo hozzaferes soran!");
        return(-1);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
         lines++;
    }
    fclose(fp);
    return lines;

}
void fileNumbers(char *filename,int* intArray,int linesNumber){
    FILE *fp=fopen(filename,"r");
    int array[linesNumber];
    int i;
    
    for (i = 0; i < linesNumber; i++) {
        fscanf(fp, "%d", intArray+i);
    }
    fclose(fp);
}
void sumCalc(int *sum, int* intArray, int length){
    int i;
    for (i = 0; i < length; i++)
    {
        *sum+=intArray[i];
    }
}
void minCalc(int *sum, int* intArray, int length){
    int i;
    for (i = 0; i < length; i++)
    {
        if (intArray[i]<*sum)
        {
            *sum=intArray[i];
        }
        
    }
}
void maxCalc(int *sum, int* intArray, int length){
    int i;
    for (i = 0; i < length; i++)
    {
        if (intArray[i]>*sum)
        {
            *sum=intArray[i];
        }
        
    }
}
void sumCalcR(int *sumR, int* intArray, int length){
    if(length>0){
        sumCalcR(sumR,intArray,length-1);
    }
    *sumR+=intArray[length];
}
void minCalcR(int *minR, int* intArray, int length){
    if(length>0){
        minCalcR(minR,intArray,length-1);
    }
    if (intArray[length]<*minR)
    {
        *minR=intArray[length];
    }

}
void maxCalcR(int *maxR, int* intArray, int length){
    if(length>0){
        maxCalcR(maxR,intArray,length-1);
    }
    if (intArray[length]>*maxR)
    {
        *maxR=intArray[length];
    }

}