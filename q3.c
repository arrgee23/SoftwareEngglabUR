/**
        Rahul Gautam(59), Aniruddha Mukherjee(56), Souradip Roy(54) 20/02/2016
        Software engineering Sec 1 
        Finding count of vowels from a very large array using threads
        compilation: gcc vowelcount.c -lpthread
        execution: ./a.out
        change the number of threads by changing the global  variable NUM_THREADS on line 25
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define SIZE 100000000
#define ALPHABET_SIZE 26
#define NO_OF_VOWELS 5


char* array;

//pthread_mutex_t minMutex; // mutex
long counts[ALPHABET_SIZE]; // associative array holding count of each vowel
char vowels[] = {'a','e','i','o','u'};
struct thread_data{
   char toCompare[5];
   int count;
};



void *countVowel(void* c){
    struct thread_data* in = (struct thread_data*) c;

    char* letters = in->toCompare;
    int len = in->count;

    /*int i=0;
    for (int i = 0; i < len; ++i)
    {
    	printf("%c ",letters[i] );
    }
    puts("");
    */

    int i=0;    
    for (i = 0; i < SIZE; ++i){
        int j;
        for (j = 0; j < len; ++j){
        	if (array[i]==letters[j]){
        		counts[letters[j]]++;
        	}
        }
    }        

}        


int main(int argc, char const *argv[]){
        int NUM_THREADS;
        //scanf("%d",&NUM_THREADS);
		NUM_THREADS = atoi (argv[1]);
        srand(time(NULL));

        // set max num thread to 5
        if(NUM_THREADS>5)
        	NUM_THREADS=5;

        // initialize counts array 
        int j=0;
        for (j = 0; j < ALPHABET_SIZE; ++j)
    	{
        	counts[j]=0;
    	}

        pthread_t threads[NUM_THREADS];


        // populate array
        array = (char*)malloc(SIZE*sizeof(char));
        if(array==0){
                puts("No memory available");
                return 0;
        }

        //printf("character Set: ");
        for(j=0;j<SIZE;j++){
                char randomletter = "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
                array[j] = randomletter;
        }

        /*for (int i = 0; i < SIZE; ++i)
        {
        	printf("%c ",array[i]);
        }
        puts("");
		*/

        long i=0;
        struct timeval start, end;
        gettimeofday(&start, NULL);

        // thread data passing
        struct thread_data thread_data_array[NUM_THREADS];

        for (i = 0; i < NUM_THREADS; ++i)
        {
        	thread_data_array[i].count=0;
            int k = i;
            while(k<5){
            	thread_data_array[i].toCompare[thread_data_array[i].count]=vowels[k];
                thread_data_array[i].count++;
                k += NUM_THREADS;
            }
            pthread_create(&threads[i],NULL,countVowel,(void*)&thread_data_array[i]);
        }

        for (i=0;i<NUM_THREADS;++i){
            pthread_join(threads[i],NULL);
        }

        gettimeofday(&end, NULL);
        printf("Microseconds: %ld for %d threads\n", ((end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec)),NUM_THREADS);
        
        printf("a: %ld\n",counts['a']);
        printf("e: %ld\n",counts['e']);
        printf("i: %ld\n",counts['i']);
        printf("o: %ld\n",counts['o']);
        printf("u: %ld\n",counts['u']);
        
        return 0;
}


