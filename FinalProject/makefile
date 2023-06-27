IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -O0 -std=c++11
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmultichar"
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic pop


ODIR=.

LIBS=-lncurses -lstdc++

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o model.o classes.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: finalproject

finalproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f  finalproject
	rm -f *.o
	
etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append  
