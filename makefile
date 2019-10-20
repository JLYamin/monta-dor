IDIR	=./include
CC      = g++ -std=c++14
CFLAGS  = -Wall -g -I$(IDIR) --coverage
GCOVFLAGS = $(CFLAGS) --coverage -fPIC  -O0

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src
TDIR	=./tests

LIBS	=-lm

_DEPS	= leitor.hpp tabelas.hpp preprocessador.hpp escritor.hpp analisador.hpp simulador.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TOBJ = leitor.o tabelas.o analisador.o preprocessador.o escritor.o tests_main.o tests_analisador.o
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

_OBJ = leitor.o tabelas.o analisador.o preprocessador.o escritor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ_SIMULADOR = $(_OBJ) simulador.o
OBJ_SIMULADOR = $(patsubst %,$(ODIR)/%,$(_OBJ_SIMULADOR))

_OBJ_MONTADOR = $(_OBJ) montador.o
OBJ_MONTADOR = $(patsubst %,$(ODIR)/%,$(_OBJ_MONTADOR))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

analisador_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_assembler: $(TOBJ)
	$(CC) -o $@ $^ $(GCOVFLAGS) $(LIBS)

montador: $(OBJ_MONTADOR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

simulador: $(OBJ_SIMULADOR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcovr_html:
	gcovr -r . --html --html-details -o ./tests/gcov/tests-detailts.html

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(ODIR)/*.gcno *~ core $(INCDIR)/*~
	rm -f $(ODIR)/*.gcda *~ core $(INCDIR)/*~
