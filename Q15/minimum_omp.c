/**************************************************
	DESCRIPTION: This finds the minimum value in an 
	unsigned array of integers using OMP in C.The 
	integers are randomly defined.
	AUTHOR: Souradip Roy
	ROLL NO: 54
**************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

	omp_set_dynamic(0);
	omp_set_num_threads(numThreads);

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

	#pragma omp parallel for reduction(min : globalMin)
  	for (i=0; i<arraySize; i++)
  	{
  		globalMin=MIN(globalMin,array[i]);
  	}

	gettimeofday(&end,NULL);

	/*
		Print results and relevant info.
	*/
	printf("Minimum: %u\n",globalMin);
	printf("Time Needed (ms): %ld\n", ((end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec)));
	
	return 0;
}
