/**
        Rahul Gautam(59), Aniruddha Mukherjee(56), Souradip Roy(54) 24/02/2016
        Software engineering Sec 1 
        zip permutation
        compilation: g++ 2.cpp -lpthread
        execution: ./a.out
*/


#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<pthread.h>
#include<unistd.h>
#include<limits.h>
#include<math.h>
#define MAX 10
//#define PERThread 100000

using namespace std;

pthread_mutex_t MUTEX;
pthread_barrier_t BARRIER;

vector<int> input;
vector<int> output;

int bias;

class range{
public:   int l1,h1;
          int l2,h2;


          range(){}

          range(int low1,int high1,int low2,int high2)
          {
            l1=low1;
            h1=high1;
            l2=low2;
            h2=high2;
          }
};


void * permutation(void *data)
{
 range *item=(range*)  data;
 //cout<<"what is happening";

//cout<<"\npermutation called "<<item->l1<<" "<<item->h1<<" "<<item->l2<<" "<<item->h2;

pthread_mutex_lock(&MUTEX);

for(int i=item->l1;i<=item->h1;i++)
  output[i*2]=input[i];

  for(int i=item->l2;i<=item->h2;i++)
    output[(i-bias)*2+1]=input[i];

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
int N=1,K=0;
pthread_mutex_init(&MUTEX, NULL);

while(N%2 !=0 || N==0)
{
  cout<<"Enter array Length: ";
  cin>>N;
}

while(K==0){
  cout<<"Enter number of Threads: ";
  cin>>K;
}

if(K==1)
  K++;

  if(K > N/2)
  {
    K=N/2;
    cout<<"No of threads auto adjusted to "<<K<<endl;
  }



output.resize(N,0);

for(int i=0;i<N;i++)
  {
    input.push_back(rand()%MAX);
  }

cout<<"Array before Zip permutation:\n";

for(int i=0;i<input.size();i++)
    cout<<input[i]<<"\t";
puts("\n");

int perThread= ceil_div(input.size(),2)/K;
//cout<<"\nperThread= "<<perThread;
bias=N/2;
//cout<<"\nBias= "<<bias;

int flag=(N-perThread*K*2);
//cout<<"remaining elements= "<<flag;

pthread_t threads[K];

pthread_barrier_init(&BARRIER,NULL,K);

int j;
for(int i=0;i<K;i++)
{
    //cout<<"Thread call";
   j=i*perThread;
    //cout<<j<<(j+perThread-1)<<j+bias<<j+bias+perThread-1;
    //cout<<"last element= "<<j<<endl;
    range *data =new range(j,(j+perThread-1),j+bias,j+bias+perThread-1);
    pthread_create(&threads[i], NULL, permutation,data);

    //pthread_join(threads[i],NULL);
}

pthread_barrier_wait(&BARRIER);

  //usleep(10000);

pthread_barrier_destroy(&BARRIER);

if(flag)
{
  //range *data =new range(j+1,bias-1,j+1+bias,N-1);

  for(int i=j+1;i<bias;i++)
    output[i*2]=input[i];

    for(int i=j+1+bias;i<N;i++)
      output[(i-bias)*2+1]=input[i];

}

cout<<"\nArray after Zip permutation:\n";

input=output;

for(int i=0;i<output.size();i++)
    cout<<output[i]<<"\t";

puts("\n");
//usleep(5000);


  return 0;
}
