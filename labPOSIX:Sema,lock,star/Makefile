GCC = gcc
FLAGS = -Wall -pthread

PROGRAMAS = lab01 lab02 lab03 lab04 lab05 lab06 lab07 lab08
RM = rm -rf

all: $(PROGRAMAS)

%: %.c
	$(GCC) $(FLAGS) $< -o $@

run%:
	./lab0$*

clean:
	$(RM) $(PROGRAMAS)

update: clean all