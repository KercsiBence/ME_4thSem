#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

#define N 500
#define THREADNUMBER 10


struct arg_struct {
	int* array;
    int thread_from;
	int odd;
	int even;
	int zero;
	int negativ;
}args;


void get_sum_of_array(void* param1)
{
	int i;
	int *array;
	struct arg_struct *arguments = param1;
	
	array=arguments->array;
	i=arguments->thread_from;
	
	
	for(;i<N;i+=THREADNUMBER){
		if(array[i]==0){
			arguments->zero++;
		}else if(array[i]%2==0){
			arguments->even++;
		}else{
			arguments->odd++;
		}
		if(array[i]<0){
			arguments->negativ++;
		}
	}
}


int main(int argc, char* argv[])
{
	int array[N],i,odd,even,negativ,zero;
	pthread_t threads[THREADNUMBER];
	struct arg_struct arguments[THREADNUMBER];
	srand(time(NULL));
	clock_t begin,end;
	double time;
	
	odd=0;
	even=0;
	negativ=0;
	zero=0;
	begin = clock();
	
	for(i=0;i<N;i++){
		array[i]=rand()%200-100;
	}
	for(i=0;i<THREADNUMBER;i++){
		arguments[i].thread_from = i;
		arguments[i].array = array;
		arguments[i].odd = 0;
		arguments[i].even = 0;
		arguments[i].zero = 0;
		arguments[i].negativ = 0;
		pthread_create(&threads[i], NULL, get_sum_of_array, (void *)&arguments[i]);
	}
	
	for(i=0;i<THREADNUMBER;i++){
		pthread_join(threads[i], NULL);
	}
	
	for(i=0;i<THREADNUMBER;i++){
		odd+=arguments[i].odd;
		even+=arguments[i].even;
		negativ+=arguments[i].negativ;
		zero+=arguments[i].zero;
	}
	printf("\nodd:%d\neven:%d\nzero:%d\nnegativ:%d\n",odd,even,zero,negativ);
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time: %lf",time);
	sleep(1);
	return 0;
}
