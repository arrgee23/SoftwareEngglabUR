/**
	Rahul Gautam, Aniruddha Mukherjee, Souradip Roy 09/02/2016
	Software engineering Sec 1 problem 1
	Finding minimum of a very large array using threads

	compilation: gcc thread1.c -lpthread
	execution: ./a.out
	change the number of threads by changing the global  variable NUM_THREADS on line 25
*/

/**
	Size: 100000000
	time taken with 5 threads: 0.317896
	time taken with 10 threads: 0.407415
	time taken with 100 threads: 1.032361

	Size: 1000000000

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 64
#define SIZE 100000000
#define UCHAR_MAX 255

unsigned char* array;
//pthread_mutex_t minMutex; // mutex
unsigned char* candidateMins; // min calculated by each thread

/*
	finds minimum by ith thread iterating over only integer 
	multiples of i as index in the array
*/
void *findMin(void* threadId){
	long threadNo = *((long*)threadId);
	long i = threadNo;
	int min = 2000;
	while(i<SIZE){

		if(array[i]<min){
			// use of mutex
			//pthread_mutex_lock (&minMutex);
			candidateMins[threadNo] = array[i];	
			min = array[i];
			//pthread_mutex_unlock (&minMutex);
		}

		i += NUM_THREADS;
	}
}

int main(int argc, char const *argv[]){
	pthread_t threads[NUM_THREADS];
	long arguments[NUM_THREADS];
	


	// populate array
	array = (unsigned char*)malloc(SIZE*sizeof(unsigned char));
	if(array==0){
		puts("No memory available");
		return 0;
	}
	
	
	long i=0;
	for(i=0;i<SIZE;i++){
		array[i]=rand()%(UCHAR_MAX+1); // o to UCHAR_MAX range
		//printf("%d ",array[i]);
	}
	//puts("");


	// initialize mutex
	//pthread_mutex_init(&minMutex, NULL);

	// allocate memory for thread individual min calculation array
	candidateMins = (unsigned char*) malloc(NUM_THREADS*sizeof(unsigned char));

	// calculate the execution time
	clock_t t;
    t = clock();
	for (i = 0; i < NUM_THREADS; ++i)
	{
		arguments[i]=i;
		pthread_create(&threads[i],NULL,findMin,(void*)&arguments[i]);
		pthread_join(threads[i],NULL);
	}
	// calculate mins form the individual thread  mins
	int min = 5000;
	for (i = 0; i < NUM_THREADS; ++i)
	{
		if(candidateMins[i]<min)
			min=candidateMins[i];
	}
	t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("min is %d\n",min);
	printf("time taken with %d threads: %f\n",NUM_THREADS,time_taken);
	

	
	return 0;
}
