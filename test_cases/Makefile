CC = gcc
CXX = g++
AR = ar
LD = ld

CFLAGS = -g -std=gnu99 -Wall -I./ -I../

POBJS = 

TEST_MAIN = test

SRC = test_ring_buffer.c ../ring_buffer.c

TARGET_ALL = $(TEST_MAIN)

all: $(TARGET_ALL)

$(TEST_MAIN):
	gcc -o $@ $(SRC) $(CFLAGS)
	
	
clean:
	rm -f *.o ../*.o $(TARGET_ALL)
