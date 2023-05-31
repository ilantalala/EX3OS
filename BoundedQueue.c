#include "BoundedQueue.h"
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>



void init_BoundedQueue(BoundedQueue* queue) {
    sem_init(&queue->full, 0, 0);
    sem_init(&queue->empty, 0, MAX_SIZE);
    queue->front=-1;
    queue->rear=-1;
    queue->arr[0]=NULL;
    pthread_mutex_init(&queue->locker, NULL);
}
BoundedQueue* arr_queue[MAX_SIZE];
int isQueueEmpty(BoundedQueue* queue){
    return (queue->rear==-1&&queue->front==-1);
}
int isQueueFull(BoundedQueue* queue){
    return ((queue->rear+1)%MAX_SIZE==queue->front);
}
void push(BoundedQueue* queue,char* string){
    sem_wait(&queue->empty);
    printf("passed\n");
    pthread_mutex_lock(&queue->locker);
    if(isQueueFull(queue)){
        printf("The queue is full, cannot push\n");
    }
    if(isQueueEmpty(queue)){
        queue->front=0;
        queue->rear=0;
    }
    else{
        queue->rear=(queue->front+1)%MAX_SIZE;
    }
    queue->arr[queue->rear]=string;
    pthread_mutex_unlock(&queue->locker);
    sem_post(&queue->full);
}
char* pop(BoundedQueue* queue){
    sem_wait(&queue->full);
    pthread_mutex_lock(&queue->locker);
    char* string;
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot pop.\n");
        string=NULL;
    }
    string=queue->arr[queue->front];
    if(queue->front==queue->rear)
    {
        queue->rear=-1;
        queue->front=-1;
    }
    else{
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
    pthread_mutex_unlock(&queue->locker);
    sem_post(&queue->empty);
    return string;
}
void* pushThread(void* arg) {
    // Perform the push operation
    char* string = "Hello";
    push(arr_queue[0], string);
    pthread_exit(NULL);
}

void* popThread(void* arg) {
    BoundedQueue* queue = (BoundedQueue*)arg;

    // Perform the pop operation
    char* value = pop(queue);

    printf("Popped value: %s\n", value);

    pthread_exit(NULL);
}
void freeBoundedQueue(BoundedQueue* queue) {
    // Free the memory for each element in the array

    free(queue->arr[0]);
    queue->arr[0]=NULL;

    // Destroy the mutex and semaphores
    pthread_mutex_destroy(&queue->locker);
    sem_destroy(&queue->full);
    sem_destroy(&queue->empty);

    // Free the memory for the queue structure
    free(queue);
}