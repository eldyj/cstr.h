CC = gcc
FLAGS = -O3 -Wall -Wextra
CCF = $(CC) $(FLAGS)
BIN = bin
SRC = src

bin:
	mkdir -p $(BIN)

cstr.c: bin
	$(CCF) -c -o$(BIN)/cstr.o $(SRC)/cstr.c

cstr.o: cstr.c
	ar rcs $(BIN)/libcstr.a $(BIN)/cstr.o

install: cstr.o
	cp $(SRC)/cstr.h /usr/local/include
	cp $(BIN)/libcstr.a /usr/local/lib
