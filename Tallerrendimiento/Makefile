#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
#     Fecha: 14/11/2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización de compilacion y comandos diversos
#****************************************************************/

GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

PROGRAMAS = mmClasicaOpenMP mmClasicaFork mmClasicaPosix mmFilasOpenMP

All: $(PROGRAMAS)

mmClasicaFork:
	$(GCC) $(CLFAGS) $@.c moduloClasicaFork.c -o $@ 

mmClasicaOpenMP:
	$(GCC) $(CLFAGS) $@.c moduloClasicaOpenMP.c -o $@ $(FOPENMP)

mmFilasOpenMP:
	$(GCC) $(CLFAGS) $@.c moduloFilasOpenMP.c -o $@ $(FOPENMP)

mmClasicaPosix:
	$(GCC) $(CLFAGS) $@.c moduloClasicaPosix.c -o $@ 

clean:
	$(RM) $(PROGRAMAS) 