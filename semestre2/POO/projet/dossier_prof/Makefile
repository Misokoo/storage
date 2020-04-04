CC=g++
CFLAGS=-std=c++11 -Wall -g #-DDEBUG

EXE=echecs

SRC=echecs-main.cc square.cc echiquier.cc piece.cc jeu.cc
OBJ=echecs-main.o  square.o  echiquier.o  piece.o  jeu.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $@

SUFFIXES:.cc .o

echecs-main.o : echecs-main.cc echiquier.cc jeu.cc
	$(CC) $(CFLAGS) -c $<

jeu.o: jeu.cc echiquier.h piece.h square.h
	$(CC) $(CFLAGS) -c $<

echiquier.o : echiquier.cc piece.h square.h
	$(CC) $(CFLAGS) -c $<

piece.o: piece.cc piece.h square.h echiquier.h
	$(CC) $(CFLAGS) -c $<

square.o : square.cc square.h
	$(CC) $(CFLAGS) -c $<


clean:
	rm -rf $(EXE) *.o *.dSYM *~ 
