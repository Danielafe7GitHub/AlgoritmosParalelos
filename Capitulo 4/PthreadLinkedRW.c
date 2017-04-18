#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
/*Compilar gcc -g -Wall -o linked PthreadLinkedRW.c -lpthread */

#define  members 800
#define  inserts 100
#define  deletes 100

/******************Time Variables*********************************/
clock_t timeInsert;
clock_t timeMember;
clock_t timeDelete;

float timeInsertTotal,timeMemberTotal,timeDeleteTotal = 0;
pthread_rwlock_t rwlock;

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
    temp_p = malloc(sizeof(struct list_node_s));
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

void Cant_Insert(int cant){
  int i;
  for(i = 0; i < cant; i++) {
    pthread_rwlock_wrlock(&rwlock);
    Insert(1000,&list);/*Se inserta el valor 1000 cant de veces*/
    pthread_rwlock_unlock(&rwlock);
  }
  return;
}

void Cant_Member(int cant){
  int i;
  for(i = 0; i < cant; i++) {
    pthread_rwlock_rdlock(&rwlock);
    Member(1000,list);/*Se verifica existencia del valor 1000 cant de veces*/
    pthread_rwlock_unlock(&rwlock);
  }
  return;
}

void Cant_Delete(int cant){
  int i;
  for(i = 0; i < cant; i++) {
    pthread_rwlock_wrlock(&rwlock);
    Delete(1000,&list);
    pthread_rwlock_unlock(&rwlock);
  }
  return;

}



void* Operaciones(void* rank){
  long my_rank = (long) rank;

  timeMember = clock();
  Cant_Member(members);
  timeMember = clock() - timeMember;
  //printf("Member %lf\n", (((float)timeMember)/CLOCKS_PER_SEC));
  timeMemberTotal+= (((float)timeMember)/CLOCKS_PER_SEC);
  
  timeInsert = clock();
  Cant_Insert(inserts);
  timeInsert = clock() - timeInsert;
  //printf("Insert %lf\n", (((float)timeInsert)/CLOCKS_PER_SEC));
  timeInsertTotal+= (((float)timeInsert)/CLOCKS_PER_SEC);

  timeDelete = clock();
  Cant_Delete(deletes);
  timeDelete = clock() - timeDelete;
  //printf("Delete %lf\n", (((float)timeDelete)/CLOCKS_PER_SEC));
  timeDeleteTotal+= (((float)timeDelete)/CLOCKS_PER_SEC);
  return NULL;
}



int main(int argc, char* argv[]){

	/***************************************************/
    long thread;
	double thread_count;
	pthread_t *thread_handles;
	struct list_node_s* list = NULL;
    pthread_rwlock_init(&rwlock,NULL);
    thread_count = strtol(argv[1],NULL,10);
	thread_handles = malloc(thread_count* sizeof(pthread_t));

    for(thread=0;thread<thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,Operaciones,(void*)thread);
    }
	for(thread=0;thread<thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }
	
	printf("Insert Total %lf\n", timeInsertTotal);
	printf("Member Total %lf\n", timeMemberTotal);
	printf("Delete Total %lf\n", timeDeleteTotal);
	printf("Promedio Total %lf\n", (timeDeleteTotal+timeInsertTotal+timeMemberTotal)/3);

    return 0;
}
