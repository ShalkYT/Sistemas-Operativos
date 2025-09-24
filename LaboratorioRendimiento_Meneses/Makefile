GCC = gcc
PROGRAMAS = labRendiMeneses
MODULOS = modulo

labRendiMeneses:
	$(GCC) $(MODULOS).c -c
	$(GCC) $@.c $(MODULOS).o -o $@
	rm -f $(MODULOS).o

clear:
	rm -f $(PROGRAMAS)
