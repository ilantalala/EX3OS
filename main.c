#include "BoundedQueue.h"
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
int main() {
    BoundedQueue *queue = malloc(sizeof(BoundedQueue));
    init_BoundedQueue(queue);
    arr_queue[0] = queue;
    pthread_t pushThreadId;

// Create the push thread
    if (pthread_create(&pushThreadId, NULL, pushThread, queue) != 0) {
        fprintf(stderr, "Failed to create push thread\n");
        return 1;
    }

// Create the pop thread
/*  if (pthread_create(&popThreadId, NULL, popThread, queue) != 0) {
      fprintf(stderr, "Failed to create pop thread\n");
      return 1;
  }
*/
// Wait for the threads to finish
    pthread_join(pushThreadId, NULL);
//  pthread_join(popThreadId, NULL);
// Clean up resources
    free(queue);
}