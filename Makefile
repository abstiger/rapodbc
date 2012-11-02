CC=gcc
CFLAGS=-Wall -g -O2 -fPIC -DPIC -I. -Iexamples/
LDFLAGS=-L. -Lexamples/
RAP=./rapodbc

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

all: libdbsbas.so rapodbc libexamples.so 

libdbsbas.so: dbs_basopr.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared $^ -lodbc -o $@

dbs_basopr_test: dbs_basopr_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -ldbsbas -o $@

rapodbc: rapodbc.o 
	$(CC) $(CFLAGS) $^ -lodbc -o $@	

libexamples.so: 
	@cd examples && make

dbs_examples_test:dbs_examples_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -ldbsbas -lexamples -lodbc -o $@

test: dbs_basopr_test dbs_examples_test
	@cp examples/libexamples.so .
	@export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

clean:
	@cd examples && make clean
	@rm -f *.o *.so *_test rapodbc
