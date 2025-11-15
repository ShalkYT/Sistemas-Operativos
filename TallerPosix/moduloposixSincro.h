#ifndef __MODULOPOSIXSINCRO_H__
#define __MODULOPOSIXSINCRO_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>    
#include <sys/mman.h>  
#include <semaphore.h>  
#include <pthread.h>

#define MAX_BUFFERS 10

extern char buf [MAX_BUFFERS] [100];
extern int buffer_index;
extern int buffer_print_index;

extern pthread_mutex_t buf_mutex;
extern pthread_cond_t buf_cond;
extern pthread_cond_t spool_cond;
extern int buffers_available;
extern int lines_to_print;

void *producer (void *arg);
void *spooler (void *arg);

#endif 