# Part of pkmath package
# author Antonio AKA Lord Feistel

OBJS	= euclidean.o pkmath.o tests.o
SOURCE	= euclidean.cpp pkmath.cpp tests.cpp
HEADER	= 
OUT		= pkmath
CC	 	= g++
FLAGS	= -g -c -Wall -std=c++17
LFLAGS	= 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

euclidean.o: euclidean.cpp
	$(CC) $(FLAGS) euclidean.cpp 

teste.o: teste.cpp
	$(CC) $(FLAGS) tests.cpp 


clean:
	rm -f $(OBJS) $(OUT)
