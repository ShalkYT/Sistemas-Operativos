# Pontificia Universidad Javeriana
# Autor: Andres Eduardo Meneses Rincon


# Compilador
GCC = gcc
# Flags de compilacion
FLAGS =
# Comando de eliminacion
RM = rm -f

# Archivos adicionales para la compilacion (Modulos)
MODUlO = modulo.c

# Nombre de los programas a compilar
PROGRAMAS = cliente servidor

# Compilacion del cliente
cliente:
	$(GCC) $(FLAGS) $(MODUlO) $@.c -o $@

# Compilacion del servidor
servidor:
	$(GCC) $(FLAGS) $(MODUlO) $@.c -o $@

# Comando para eliminar los archivos compilados
clear:
	$(RM) $(PROGRAMAS)
