IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -O0 -std=c++11

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o classes.o model.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: a5

a5: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f  a5
	rm -f *.o
	
etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append  
