#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>    
#include <sys/mman.h> 
#include <semaphore.h> 

#define BUFFER 20

typedef struct{
    int entrada;
    int bus[BUFFER];
}compartir_datos;

int main() {
    sem_t *vacio = sem_open("/vacio", O_CREAT, 0644, BUFFER);
    sem_t *lleno = sem_open("/lleno", O_CREAT, 0644, 0);
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    int shm_fd = shm_open("/memoria_compartida", O_CREAT | O_RDWR, 0644);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(compartir_datos));

    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    compartir->entrada = 0;

    for (int i = 1; i <= 10; i++) {
        sem_wait(vacio);
        compartir->bus[compartir->entrada] = i;
        printf("Productor: Produce%d\n", i);
        compartir->entrada = (compartir->entrada+1) % BUFFER;
        sem_post(lleno);
        sleep(1);  
    }

    munmap(compartir, sizeof(compartir_datos));
    close(shm_fd);
    sem_close(vacio);
	sem_unlink("/vacio");
    shm_unlink("/memoria_compartida");
    return 0;
}
