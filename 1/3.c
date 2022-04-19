#include <stdio.h>
#include <time.h>
#include <stdlib.h>




int main(int argc, char* argv[])
{
	int number1;
	int number2;
	srand(time(0));
	int sum,input,time;
	clock_t begin,end;
	
	
	number1=rand()%100;
	number2=rand()%100;
	sum=number1+number2;
	
	
	begin = clock();
	printf("What is the sum?\n%d+%d\n",number1,number2);
	scanf("%d",&input);
	end = clock();
	time = (int)(end - begin) / CLOCKS_PER_SEC;
	if(input==sum){
		printf("Correct!\nYour time:%d",time);
		return 0;
	}
	printf("Incorrect!\nThe correct answer:%d\nYour answer:%d\nTime:%d",sum,input,time);
	
	return 0;
}
