# Makefile Variables
CC = g++
CFLAGS  = -g -Wall
STD = -std=c++11
INCL_DIRS = -I$(CURDIR)/../
LIBS = -lneo4j-client -lssl -lcrypto -lm
RM = rm -f

#Makefile Targets
tests: neo4j_test

clean:
	$(RM) *.o *~ *_test

# Test
# Create the executable file zmqio_test
neo4j_test: neo4j_test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(STD) $(INCL_DIRS)

# Create the object file zmqio_test.o
neo4j_test.o: neo4j_test.cpp
	$(CC) $(CFLAGS) -o $@ -c neo4j_test.cpp $(STD) $(INCL_DIRS)
