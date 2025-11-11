##################################################
#	Pontificia Universidad Javeriana
# Autor: Andres Eduardo Meneses Rincon
# Materia:Sistemas operativos
# Fichero: Automatizacion compilación
##################################################

# Compilador
GCC = gcc
# Banderas que se utilizan
FLAGS = -fopenmp -lm

# Variable para simplificar el comando de eliminacion
RM = rm -rf

# Todos los programas que tiene el laboratorio
PROGRAMAS = labOMP01 labOMP02 labOMP03 labOMP04 labOMP05 labOMP06

all: $(PROGRAMAS)

# Compilacion del pimer programa
labOMP01:
	$(GCC) $@.c -o $@ $(FLAGS)

# Compilacion del segundo programa
labOMP02:
	$(GCC) $@.c -o $@ $(FLAGS)

# Compilacion del segundo programa
labOMP03:
	$(GCC) $@.c -o $@ $(FLAGS)

# Compilacion del segundo programa
labOMP04:
	$(GCC) $@.c -o $@ $(FLAGS)

# Compilacion del quinto programa
labOMP05:
	$(GCC) $@.c -o $@ $(FLAGS)

# Compilacion del quinto programa
labOMP06:
	$(GCC) $@.c -o $@ $(FLAGS)

# Eliminacion de ejecutables
clear:
	$(RM) $(PROGRAMAS)
