
#ifndef EX3OS_BOUNDEDQUEUE_H
#define EX3OS_BOUNDEDQUEUE_H
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#define MAX_SIZE 2

typedef struct {
    char* arr[MAX_SIZE];
    int front;
    int rear;
    pthread_mutex_t locker;
    sem_t full;
    sem_t empty;
} BoundedQueue;
extern BoundedQueue* arr_queue[];
void init_BoundedQueue(BoundedQueue* queue);

char* getFront(BoundedQueue* queue);
int isQueueEmpty(BoundedQueue* queue);
int isQueueFull(BoundedQueue* queue);
void push(BoundedQueue* queue,char* string);
char* pop(BoundedQueue* queue);
void* pushThread(void* arg);
void* popThread(void* arg);
void freeBoundedQueue(BoundedQueue* queue);
#endif // EX3OS_BOUNDEDQUEUE_H