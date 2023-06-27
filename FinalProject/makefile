IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -O0 -std=c++11

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
