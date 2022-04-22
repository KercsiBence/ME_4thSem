#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 15
#define N 20

typedef struct data
{
	char* alphabet;
	int alphabet_size;
	int password_size;
	bool password_found;
}Data;

char password[MAX_SIZE];

void crack_password(Data* data){
	char characters[data->password_size];
	int i,random;
	
	while(data->password_found==false){
		for(i=0;i<data->password_size;i++){
			random=rand()%data->alphabet_size;
			characters[i]=data->alphabet[random];
		}
		if(strncmp(characters,password,data->password_size)==0){
			data->password_found=true;
		}
	}
}

int main(int argc, char* argv[])
{
	Data data;
	pthread_t thread[N];
	int i,k,random;
	clock_t t;
	double cpu_time_used;
	
	data.alphabet="0123456789";
	data.alphabet_size=10;
	srand(time(NULL));
	
	
	//sebesség ellenörzése különböző szál méretekkel és jelszó mérettel
	for(k=1;k<MAX_SIZE;k++){
		data.password_size=k;
		data.password_found=false;
		for(i=0;i<data.password_size;i++){
			password[i]=data.alphabet[rand()%data.alphabet_size];
		}
		t = clock();
		for(i=0;i<N;i++){
			pthread_create(&thread[i], NULL, crack_password, &data);
		}
		for(i=0;i<N;i++){
			pthread_join(thread[i], NULL);
		}
		t = clock()-t;
		cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
		printf("Password found!!!\ttime: %f\tsize: %d\tthreads: %d\t%s\n",cpu_time_used,k,N,password);
	}
	
	
	
	
	return 0;
}