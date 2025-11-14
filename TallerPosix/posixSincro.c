#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>      // O_CREAT, O_RDWR
#include <sys/mman.h>   // shm_open, mmap
#include <semaphore.h>  // sem_open, sem_wait, sem_post
#include <pthread.h>

#define MAX_BUFFERS 10

char buf [MAX_BUFFERS] [100];
int buffer_index;
int buffer_print_index;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;
int buffers_available = MAX_BUFFERS;
int lines_to_print = 0;

void *producer (void *arg);
void *spooler (void *arg);

int main (int argc, char **argv){
    pthread_t tid_producer [10], tid_spooler;
    int i, r;

    buffer_index = buffer_print_index = 0;
    if ((r = pthread_create (&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }
    int thread_no [10];
    for (i = 0; i < 10; i++) {
        thread_no [i] = i;
        if ((r = pthread_create (&tid_producer [i], NULL, producer, (void *) &thread_no [i])) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    }
    for (i = 0; i < 10; i++)
        if ((r = pthread_join (tid_producer [i], NULL)) == -1) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    
    while (lines_to_print) sleep (1);
    if ((r = pthread_cancel (tid_spooler)) != 0) {
        fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
    }

    exit (0);
}

void *producer (void *arg){
    int i, r;
    int my_id = *((int *) arg);
    int count = 0;

    for (i = 0; i < 10; i++) {

        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            while (!buffers_available) 
                pthread_cond_wait (&buf_cond, &buf_mutex);

            int j = buffer_index;
            buffer_index++;
            if (buffer_index == MAX_BUFFERS)
                buffer_index = 0;
            buffers_available--;

            sprintf (buf [j], "Thread %d: %d\n", my_id, ++count);
            lines_to_print++;

            pthread_cond_signal (&spool_cond);

        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    
        sleep (1);
    }
}

void *spooler (void *arg){
    int r;

    while (1) {  
        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            while (!lines_to_print) 
                pthread_cond_wait (&spool_cond, &buf_mutex);

            printf ("%s", buf [buffer_print_index]);
            lines_to_print--;

            buffer_print_index++;
            if (buffer_print_index == MAX_BUFFERS)
               buffer_print_index = 0;

            buffers_available++;
            pthread_cond_signal (&buf_cond);

        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }

    }
}
