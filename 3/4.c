#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 3000

void generate_password(FILE *fp,char* array);
void generate_password_recursive(FILE *fp,int size,char* array);

int main(int argc, char* argv[])
{
	FILE *fp;
	struct timeval stop, start;
	char array[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','0','_',' ','\n'};
	
	srand(time(NULL));
	fp=fopen("generate_pasword.txt","w");
	
	
	gettimeofday(&start, NULL);
	generate_password(fp,array);
	fclose(fp);
	gettimeofday(&stop, NULL);
	printf("\ntime: %lu \n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	
	gettimeofday(&start, NULL);
	fp=fopen("generate_password_recursive.txt","w");
	generate_password_recursive(fp,N,array);
	fclose(fp);
	gettimeofday(&stop, NULL);
	printf("\ntime: %lu \n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
	return 0;
}


void generate_password(FILE *fp,char* array){
	int i,counter;
	char characters;
	
	counter=0;
	
	for(i=0;i<N;i++){
		characters=array[rand()%39];
		fprintf(fp,"%c",characters);
		if(characters==' '){
			counter++;
		}
	}
	printf("Rows:%d",counter);
}

void generate_password_recursive(FILE *fp, int size,char* array){
	char characters;
	static int counter=0;
	
	if(size==-1){
		return;
	}
	
	characters=array[rand()%39];
	fprintf(fp,"%c",characters);
	if(characters==' '){
		counter++;
	}
	fprintf(fp,"%c",characters);
	size--;
	generate_password_recursive(fp,size,array);
}