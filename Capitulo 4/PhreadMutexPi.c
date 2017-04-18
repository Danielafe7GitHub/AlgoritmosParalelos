#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int thread_count;
int flag = 0;
long long n=100000000;
double sum = 0;
pthread_mutex_t mutex;

void* Thread_sum(void* rank){
  long my_rank = (long) rank;
  double factor, my_sum = 0.0;
  long long i;
  long long my_n = n/thread_count;
  long long my_first_i = my_n * my_rank;
  long long my_last_i = my_first_i + my_n;

  if(my_first_i % 2 == 0) factor = 1.0;
  else factor = -1.0;

  for(i = my_first_i; i < my_last_i; i++, factor = -factor){
    my_sum += factor/(2*i+1);
  }

  pthread_mutex_lock(&mutex);
  sum += my_sum;
  pthread_mutex_unlock(&mutex);

  return NULL;

}

int main(int argc, char* argv[]){

	/******************Time Variables*********************************/
	clock_t time;
	/***************************************************/
    long thread;
    thread_count = strtol(argv[1],NULL,10);
    vector<pthread_t> thread_handles(thread_count);
	time = clock();
    for(thread=0;thread<thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,Thread_sum,(void*)thread);
    }
	for(thread=0;thread<thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }
	time = clock() - time;
	cout<<"La suma es: "<<sum<<endl;
    cout<<"La Tiempo  es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;
    pthread_mutex_destroy(&mutex);

    return 0;
}

