IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -std=c++11 -O0

ODIR=.

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
	
all: T-1 T-2 T-3 T-4 T-5
	
T-1: T-1.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
T-2: T-2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
T-3: T-3.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
T-4: T-4.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
T-5: T-5.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f T-1
	rm -f T-2
	rm -f T-3
	rm -f T-4
	rm -f T-5
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append         
