############################################################
#		Pontificia Universidad Javeriana
#		Sistemas Operativos
#		Autores:
#		Docente: J. Corredor
#		Descripción: 
#
#############################################################

GCC = gcc
CFLAGS =
RM = -rf

PROGRAMAS = consumer concurrenciaPosix posixSincro producer

ALL: $(PROGRAMAS)

consumer:
	$(GCC) $@.c -o $@ $(FLAGS) 

concurrenciaPosix:
	$(GCC) modulo$@.c $@.c -o $@ $(FLAGS) 

posixSincro:
	$(GCC) modulo$@.c $@.c -o $@ $(FLAGS) 

producer:
	$(GCC) $@.c -o $@ $(FLAGS) 

# Comando dinamico
%: %.c
	$(GCC) $< -o $@ $(FLAGS)

clean:
	rm $(RM) $(PROGRAMAS)