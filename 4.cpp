/**
        Rahul Gautam, Aniruddha Mukherjee, Souradip Roy 16/02/2016
        Software engineering Sec 1 
        
		make a histogram of the data stored in the array. In order to do that we can consider 16 bins equally dividing the integer ranges. Write 			a thread program to print the distribution of data.

        compilation: g++ 4.cpp -lpthread
        execution: ./a.out
        change the number of threads by changing the global  variable NUM_THREADS on line 25
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<pthread.h>
#include<unistd.h>
#include<limits.h>
#include<math.h>
#define MAX 1600
#define BIN 16

using namespace std;
int area=MAX/16;
pthread_mutex_t MUTEX;
pthread_barrier_t BARRIER;

vector<int> input;

int perThread;
int histogram[BIN];

void Initialize()
{
  for(int i=0;i<BIN;i++)
    histogram[0]=0;
}

class range{
public:   int l1,h1;

          range(){}

          range(int low1,int high1)
          {
            l1=low1;
            h1=high1;
          }
};


void * create(void *data)
{
 range *item=(range*)  data;

  pthread_mutex_lock(&MUTEX);

  //cout<<"\nRecived limits are:  "<<item->l1<<" and "<<item->h1;

for(int i=item->l1;i<=item->h1;i++)
  for(int t=0;t<BIN;t++)
  {
    if(t==BIN-1)
        {
          if(input[i]>=t*area+1  && input[i]<=MAX)
                ++histogram[t];
        }
    else
    {
      if(input[i]>=t*area+1  && input[i]<=t*area+100)
            ++histogram[t];
    }

  }


    pthread_mutex_unlock(&MUTEX);

  //cout<<"autobots";
    pthread_barrier_wait(&BARRIER);


    //cout<<"finalMin element is "<<*(item->finalMin)<<endl;
}

int ceil_div(int a,int b){
int pro=a/b;

if(pro*b<a)  pro++;

return pro;
}

int main()
{
int N=0,K=0;



pthread_mutex_init(&MUTEX, NULL);

while(N<1)
{
  cout<<"Enter array Length: ";
  cin>>N;
}

while(K<1){
  cout<<"Enter number of Threads: ";
  cin>>K;
}

Initialize();

//if(K==1)    K++;

  if(K > N)
  {
    K=N;
    cout<<"No of threads auto adjusted to "<<K<<endl;
  }


for(int i=0;i<N;i++)
  {
    input.push_back(rand()%MAX);
  }

cout<<"Initial Array:\n";

for(int i=0;i<input.size();i++)
    cout<<input[i]<<"\t";
puts("\n");

 perThread=input.size()/K;
//cout<<"\nperThread= "<<perThread;


int flag=(N-perThread*K);
//cout<<"remaining elements= "<<flag;

pthread_t threads[K];

pthread_barrier_init(&BARRIER,NULL,K);

int j;
for(int i=0;i<K;i++)
{
    //cout<<"Thread call";
   j=i*perThread;
    //cout<<j<<(j+perThread-1)<<j+bias<<j+bias+perThread-1;
    //cout<<"limits are:  "<<j<<" and "<<j+perThread-1;
    range *data =new range(j,j+perThread-1);
    pthread_create(&threads[i], NULL, create,data);

    //pthread_join(threads[i],NULL);
}

pthread_barrier_wait(&BARRIER);

  usleep(1000);

pthread_barrier_destroy(&BARRIER);

if(flag)
{
  //cout<<"\nRecived limits are:  "<<j+perThread<<" and "<<N-1;

  for(int i=j+perThread;i<N;i++)
    for(int t=0;t<BIN;t++)
    {
      if(input[i]>=t*area+1  && input[i]<=t*area+100)
            ++histogram[t];
    }

}


cout<<"Created Histogram :\n";



for(int i=0;i<BIN;i++){
if(i==BIN-1)
    {
    cout<<"\nValues in range "<<i*area+1<<" to "<<MAX<<" = "<<histogram[i];
    }
  else
    cout<<"\nValues in range "<<i*area+1<<" to "<<i*area+area<<" = "<<histogram[i];
}
puts("\n");
//usleep(5000);


  return 0;
}
