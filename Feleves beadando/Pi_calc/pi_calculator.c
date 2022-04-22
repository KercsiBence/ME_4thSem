#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>



#define MAX_THREADS 20
#define MAX_STEP 2000000000


int main (int argc, const char *argv[]) {
    int i,j;
    double temp,pi,sum,cpu_time_used;
	clock_t t;

    for (j=1;j<=MAX_THREADS;j++){
		omp_set_num_threads(j);
		sum=0.0;
		t = clock();
        #pragma omp parallel for reduction(+:sum) private(temp)
        for (i=0;i<MAX_STEP;i++) {
            temp=(i+0.5)*(1.0/(double)MAX_STEP);
            sum+=4.0/(1.0+temp*temp); 
        }
		t = clock()-t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
        pi=(1.0/(double)MAX_STEP)*sum;
		
        printf("thread: %d \t\t pi: %.11lf\t\t time: %.6lf seconds\n",j, pi, cpu_time_used);
    }
	return 0;
}