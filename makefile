CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c
EXEC = c_sells_c_shells
MFLAGS = --leak-check=full

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)

memcheck:
	valgrind $(MFLAGS) ./$(EXEC)

