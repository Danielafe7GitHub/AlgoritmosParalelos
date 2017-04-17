#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;


pthread_rwlock_t rwlock;
int thread_count;
struct list_node_s{
  int data;
  struct list_node_s* next;
};

int Member(int value, struct list_node_s* head_p){
  struct list_node_s* curr_p = head_p;

  while(curr_p != NULL && curr_p->data < value){
    curr_p = curr_p->next;
  }

  if(curr_p == NULL || curr_p->data > value){
    return 0;
  }
  else {
    return 1;
  }
}

int Insert(int value, struct list_node_s** head_p){
  struct list_node_s* curr_p = *head_p;
  struct list_node_s* pred_p = NULL;
  struct list_node_s* temp_p;

  while(curr_p != NULL && curr_p->data < value){
    pred_p = curr_p;
    curr_p = curr_p->next;
  }

  if(curr_p == NULL || curr_p->data > value){
    temp_p = new list_node_s();
    temp_p->data = value;
    temp_p->next = curr_p;
    if(pred_p == NULL)
      *head_p = temp_p;
    else pred_p->next = temp_p;
    return 1;
  }
  else return 0;
}

int Delete(int value, struct list_node_s** head_p){
  struct list_node_s* curr_p = *head_p;
  struct list_node_s* pred_p = NULL;

  while(curr_p != NULL && curr_p->data < value){
    pred_p = curr_p;
    curr_p = curr_p->next;
  }

  if(curr_p != NULL && curr_p->data == value){
    if(pred_p == NULL){
      *head_p = curr_p->next;
      free(curr_p);
    }
    else{
      pred_p->next = curr_p->next;
      free(curr_p);
    }
    return 1;
  }
  else{
    return 0;
  }
}

struct list_node_s* list = NULL;

void N_Insert(double ops){
  double i;
  for(i = 0; i < ops; i++) {
    pthread_rwlock_wrlock(&rwlock);
    Insert(1000,&list);
    pthread_rwlock_unlock(&rwlock);
  }
  return;
}

void N_Member(double ops){
  double i;
  for(i = 0; i < ops; i++) {
    pthread_rwlock_rdlock(&rwlock);
    Member(1000,list);
    pthread_rwlock_unlock(&rwlock);
  }
  return;
}

void N_Delete(double ops){
  double i;
  for(i = 0; i < ops; i++) {
    pthread_rwlock_wrlock(&rwlock);
    Delete(1000,&list);
    pthread_rwlock_unlock(&rwlock);
  }
  return;

}

double members, inserts, deletes;

void* N_All(void* rank){
  long my_rank = (long) rank;
  //printf("%ld %lf %lf %lf\n", my_rank, members, inserts, deletes);
  N_Member(members);
  N_Insert(inserts);
  N_Delete(deletes);
  return NULL;
}


int main(int argc, char* argv[]){
  long thread;
  thread_count = strtol(argv[1],NULL,10);

  long thread;
  pthread_t *thread_handles;
  struct list_node_s* list = NULL;
  struct timespec begin,end;
  //double members,inserts,deletes;
  pthread_rwlock_init(&rwlock,NULL);
  
  thread_count = strtol(argv[1],NULL,10);
  vector<pthread_t> thread_handles(thread_count);
  scanf("%lf %lf %lf", &members, &inserts, &deletes);
  members = (members * 1000.0)/thread_count;
  inserts = (inserts * 1000.0)/thread_count;
  deletes = (deletes * 1000.0)/thread_count;
  for(int i = 0; i < 1000; i++){
    Insert(i,&list);
  }

  
  for(thread = 0; thread < thread_count; thread++) pthread_create(&thread_handles[thread], NULL, N_All, (void*) thread);
  for(thread = 0; thread < thread_count; thread++) pthread_join(thread_handles[thread], NULL);
 
  return 0;
}
