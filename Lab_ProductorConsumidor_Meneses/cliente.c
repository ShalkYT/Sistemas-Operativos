/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas Operativos
* Tema: Implementación de Productor Consumidor a partir de pipe named
* Descripción:
*  - Cliente que envía cadenas de texto a un servidor a través de una pipe nombrada (FIFO).
**************************************************************************************************/

// Inclusion de los modulos necesarios
#include "modulo.h"

// Declaracion y nombramiento de la pipe
#define FIFO_FILE "/tmp/PIPE_COMUNICATOR"

// Funcion principal
int main() {
   // Declaracion de variables
   int fd;
   int end_process;
   int stringlen;
   int read_bytes;
   char readbuf[80];
   char end_str[5];
   // Mensaje para notificar inicio de la ejecucion del cliente
   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
   // Apertura de la pipe en modo lectura y escritura
   fd = open(FIFO_FILE, O_CREAT|O_RDWR);
   // Inicializacion de la variable end_str
   strcpy(end_str, "end");

   // Ciclo infinito para la lectura y escritura de la pipe
   while (1) {
      // Notificacion para el usuario
      printf("Enter string: ");
      // Lectura de la cadena ingresada por el usuario
      fgets(readbuf, sizeof(readbuf), stdin);
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0';
      // Comparacion de la cadena ingresada con la cadena de fin para saber si se debe terminar el proceso
      end_process = strcmp(readbuf, end_str);

      // Condicion de salida del ciclo
      if (end_process != 0) { // Si la cadena ingresada no es "end" (Continuar el proceso)
         // Escritura de la cadena ingresada en la pipe
         write(fd, readbuf, strlen(readbuf));
         // Mensaje para notificar la cadena enviada y su tamaño
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         // Lectura de la cadena invertida desde la pipe
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         readbuf[read_bytes] = '\0';
         // Mensaje para notificar la cadena recibida y su tamaño
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else { // Si la cadena ingresada es "end" (Terminar el proceso)
         // Escritura de la cadena "end" en la pipe para notificar al servidor que se debe terminar el proceso
         write(fd, readbuf, strlen(readbuf));
         // Mensaje para notificar la cadena enviada y su tamaño
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         // Cierre de la pipe y salida del ciclo
         close(fd);
         break;
      }
   }
   // Fin de la funcion main
   return 0;
}
