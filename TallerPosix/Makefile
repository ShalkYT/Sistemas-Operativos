############################################################
#		Pontificia Universidad Javeriana
#		Sistemas Operativos
#		Autores:
#		Docente: J. Corredor
#		Descripción: 
#
#############################################################

GCC = gcc
CFLAGS = -Wall
RM = -rf

PROGRAMAS = consumer concurrenciaPOsix posixSincro producer

ALL: $(PROGRAMAS)

consumer:
	$(GCC) $@.c -o $@ $(FLAGS) 

concurrenciaPOsix:
	$(GCC) $@.c -o $@ $(FLAGS) 

posixSincro:
	$(GCC) $@.c -o $@ $(FLAGS) 

producer:
	$(GCC) $@.c -o $@ $(FLAGS) 

# Comando dinamico
%: %.c
	$(GCC) $< -o $@ $(FLAGS)

clean:
	rm $(RM) $(PROGRAMAS)