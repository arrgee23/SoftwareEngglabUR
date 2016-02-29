/**************************************************
	DESCRIPTION: This finds the minimum value in an 
	unsigned array of integers using pthreads in C.
	The integers are randomly defined.
	AUTHORS: Rahul Gautam(59), Aniruddha Mukherjee(56), Souradip Roy(54)
	
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/*
	The structure of the parameter sent to each thread
*/
typedef struct 
{
	int *start;
	int size;
	unsigned int result;
} threadParam;

/*
	Each thread runs this function.
*/
void* findMin(void *p)
{
	unsigned int i, min=UINT_MAX;
	threadParam param = *((threadParam*)p);
	/*
		We run till the size sent in param. The starting location is also sent.
	*/
	for(i=0;i<param.size;i++)
	{
		unsigned int element = (param.start[i]);
		min=MIN(min,element);
	}
	/*
		Finally, fix the result
	*/
	(*((threadParam*)p)).result=min;
}

/*
	The main function
*/
int main(int argc, char* argv[])
{
	/*
		The number of threads and size of array is taken as arguments
	*/
	int numThreads = atoi (argv[1]);
	int arraySize = atoi (argv[2]);

	printf("Threads : %u\n",numThreads);
	printf("ArraySize : %u\n",arraySize);

	unsigned int globalMin = UINT_MAX;

	pthread_t thread[numThreads];
	threadParam params[numThreads];

	int *array = malloc(arraySize*sizeof(int));
	srand(time(NULL));

	int i;
	for(i=0;i<arraySize;i++)
	{
		/*
			Filling up the array with random numbers.
		*/
		array[i] = rand() % (UINT_MAX);
	}

	/*
		We start timer after filling up the array.
	*/
	struct timeval start, end;
	gettimeofday(&start,NULL);

	/*
		Staart threads.
	*/
	for(int i=0;i<numThreads;i++)
	{
		params[i].start = &array[i*(arraySize/numThreads)];
		/*
			The last thread will receive the extra chunk if array%numThreads is not 0.
		*/
		params[i].size = i==numThreads-1?MAX(arraySize/numThreads, arraySize-(i)*(arraySize/numThreads)):arraySize/numThreads;
		pthread_create(&thread[i], NULL, findMin, &params[i]);
	}

	/*
		Join threads
	*/
	for(int i=0;i<numThreads;i++)
	{
		pthread_join(thread[i], NULL);
		globalMin = MIN(globalMin,params[i].result);
	}

	gettimeofday(&end,NULL);

	/*
		Print results and relevant info.
	*/
	printf("Minimum: %u\n",globalMin);
	printf("Time Needed (ms): %ld\n", ((end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec)));
	
	return 0;
}

