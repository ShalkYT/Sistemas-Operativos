GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

PROGRAMAS = mmClasicaOpenMP mmClasicaFork mmClasicaPosix mmFilasOpenMP

All: $(PROGRAMAS)

mmClasicaFork:
	$(GCC) $(CLFAGS) $@.c -o $@ 

mmClasicaOpenMP:
	$(GCC) $(CLFAGS) $@.c -o $@ $(FOPENMP)

mmFilasOpenMP:
	$(GCC) $(CLFAGS) $@.c -o $@ $(FOPENMP)

mmClasicaPosix:
	$(GCC) $(CLFAGS) $@.c -o $@ 

clean:
	$(RM) $(PROGRAMAS) 