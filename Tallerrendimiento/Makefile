#**************************************************************
#                   Pontificia Universidad Javeriana
#
#     Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
#     Fecha: 14/11/2025
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización de compilación y comandos diversos
#
#     Descripción:
#       - Makefile encargado de automatizar la compilación de los diferentes
#         programas utilizados en el taller de evaluación de rendimiento.
#       - Permite compilar versiones OpenMP, POSIX y Fork de la multiplicación
#         clásica de matrices, así como la versión por filas con OpenMP.
#       - Facilita la generación de todos los ejecutables mediante la regla "All".
#       - Incluye una regla "clean" para eliminar ejecutables generados.
#**************************************************************/

# Compilador a utilizar
GCC = gcc

# Flags generales de compilación (incluye matemáticas)
CFLAGS = -lm

# Flags para la compilación con OpenMP y nivel de optimización O3
FOPENMP = -fopenmp -O3

# Flags para la compilación con hilos POSIX (pthread)
POSIX = -lpthread

# Lista de programas que se deben compilar
PROGRAMAS = mmClasicaOpenMP mmClasicaFork mmClasicaPosix mmFilasOpenMP

# Regla principal que compila todos los programas definidos en PROGRAMAS
All: $(PROGRAMAS)

# Compilación del programa clásico con procesos (Fork)
mmClasicaFork:
	$(GCC) $(CLFAGS) $@.c moduloClasicaFork.c -o $@ 

# Compilación del programa clásico con OpenMP
mmClasicaOpenMP:
	$(GCC) $(CLFAGS) $@.c moduloClasicaOpenMP.c -o $@ $(FOPENMP)

# Compilación del programa por filas utilizando OpenMP
mmFilasOpenMP:
	$(GCC) $(CLFAGS) $@.c moduloFilasOpenMP.c -o $@ $(FOPENMP)

# Compilación del programa clásico con hilos POSIX
mmClasicaPosix:
	$(GCC) $(CLFAGS) $@.c moduloClasicaPosix.c -o $@ 

# Limpieza de los ejecutables generados
clean:
	$(RM) $(PROGRAMAS)

all: $(PROGRAMAS)
