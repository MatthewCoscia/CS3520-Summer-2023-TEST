IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -std=c++11 -O0

ODIR=.

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
	
all: 3d_dynamic 3dmatrix charptr practice_1 practice_2 struct
	
3d_dynamic: 3d_dynamic.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
3d_matrix: 3d_matrix.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
charptr: charptr.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
practice_1: practice_1.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
practice_2: practice_2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
struct: struct.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f hello
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append         
