CC = gcc
CCFLAGS = -std=gnu99
all:
	$(CROSS_COMPILE)$(CC) 5110.c $(CCFLAGS) -o 5110
