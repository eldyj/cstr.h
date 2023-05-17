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

examples/shparse.c: cstr.c
	$(CCF) -o$(BIN)/shparse $(EXM)/shparse.c $(BIN)/cstr.o

examples/scsplit.c: cstr.c
	$(CCF) -o$(BIN)/scsplit $(EXM)/scsplit.c $(BIN)/cstr.o

examples/replace.c: cstr.c
	$(CCF) -o$(BIN)/replace $(EXM)/replace.c $(BIN)/cstr.o
	
examples/strsplit.c: cstr.c
	$(CCF) -o$(BIN)/strsplit $(EXM)/strsplit.c $(BIN)/cstr.o

examples/strarrrev.c: cstr.c
	$(CCF) -o$(BIN)/strarrrev $(EXM)/strarrrev.c $(BIN)/cstr.o

examples/: examples/shparse.c examples/scsplit.c examples/replace.c examples/strsplit.c examples/strarrrev.c
examples: examples/
