#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>    
#include <sys/mman.h> 
#include <semaphore.h> 


#define BUFFER 10

typedef struct{
    int salida;
    int bus[BUFFER];
}compartir_datos;


int main() {
    sem_t *vacio = sem_open("/vacio", 0);
    sem_t *lleno = sem_open("/lleno", 0);
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    int fd_compartido = shm_open("/memoria_compartida", O_RDWR, 0644);
    if (fd_compartido < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), PROT_READ | PROT_WRITE, MAP_SHARED, fd_compartido, 0);
    compartir->salida = 0;

    for (int i = 1; i <= 10; i++) {
        sem_wait(lleno);
        int item = compartir->bus[compartir->salida];
        printf("Consumidor: Consume %d\n", item);

        compartir->salida = (compartir->salida+1) % BUFFER;

        sem_post(vacio);
        sleep(2);  
    }

    munmap(compartir, sizeof(compartir_datos));
    close(fd_compartido);
    sem_close(lleno);
    sem_unlink("/lleno");
    shm_unlink("/memoria_compartida");
    return 0;
}
