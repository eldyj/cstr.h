CC = gcc
FLAGS = -O3 -Wall -Wextra -g3
CCF = $(CC) $(FLAGS)
BIN = bin
SRC = src
EXM = examples

bin:
	mkdir -p $(BIN)

cstr.c: bin
	$(CCF) -c -o$(BIN)/cstr.o $(SRC)/cstr.c

cstr.o: cstr.c
	ar rcs $(BIN)/libcstr.a $(BIN)/cstr.o

install: cstr.o
	cp $(SRC)/cstr.h /usr/local/include
	cp $(BIN)/libcstr.a /usr/local/lib

examples/rev.c: cstr.c
	$(CCF) -o$(BIN)/rev $(EXM)/rev.c $(BIN)/cstr.o

examples/slice.c: cstr.c
	$(CCF) -o$(BIN)/slice $(EXM)/slice.c $(BIN)/cstr.o

examples/replace.c: cstr.c
	$(CCF) -o$(BIN)/replace $(EXM)/replace.c $(BIN)/cstr.o

examples/trim.c: cstr.c
	$(CCF) -o$(BIN)/trim $(EXM)/trim.c $(BIN)/cstr.o

examples/: examples/rev.c examples/slice.c examples/replace.c examples/trim.c
examples: examples/
