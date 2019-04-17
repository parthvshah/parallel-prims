CC = g++
CFLAGS =
COPTFLAGS = -O3 -g -fopenmp
LDFLAGS =

default:
	@echo "Use make prim or make clean"

#prims driver using OpenMP
prim: par.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ prim

# eof
