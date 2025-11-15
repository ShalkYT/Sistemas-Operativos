#include "moduloposixSincro.h"

char buf [MAX_BUFFERS] [100];
int buffer_index;
int buffer_print_index;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;
int buffers_available = MAX_BUFFERS;
int lines_to_print = 0;

void *producer (void *arg){
    int i, r;
    int my_id = *((int *) arg);
    int count = 0;

    for (i = 0; i < 10; i++) {

        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%d)\n", r, strerror (r)); exit (1);
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
            fprintf (stderr, "Error = %d (%d)\n", r, strerror (r)); exit (1);
        }
    
        sleep (1);
    }
}

void *spooler (void *arg){
    int r;

    while (1) {  
        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%d)\n", r, strerror (r)); exit (1);
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
            fprintf (stderr, "Error = %d (%d)\n", r, strerror (r)); exit (1);
        }

    }
}