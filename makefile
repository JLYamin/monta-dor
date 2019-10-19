IDIR	=./include
CC      = g++ -std=c++14
CFLAGS  = -Wall -g -I$(IDIR) --coverage 
GCOVFLAGS = $(CFLAGS) --coverage -fPIC  -O0 

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src
TDIR	=./tests

LIBS	=-lm
	
_DEPS	= reader_writer.hpp tabelas.hpp preprocessador.hpp escritor.hpp analisador.hpp 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TOBJ = reader_writer.o tabelas.o analisador.o preprocessador.o escritor.o tests_main.o tests_analisador.o
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

_OBJ = reader_writer.o tabelas.o  analisador.o preprocessador.o escritor.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS) 

analisador_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_assembler: $(TOBJ)
	$(CC) -o $@ $^ $(GCOVFLAGS) $(LIBS)

play_assembler: $(OBJ)
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
