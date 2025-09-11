GCC = gcc
PROGRAMAS = labRendiMeneses
MODULOS = modulo

labRendiMeneses:
	$(GCC) $(MODULOS).c -c
	$(GCC) $@.c $(MODULOS).o -o $@


clear:
	rm -f $(PROGRAMAS) $(MODULOS).o
