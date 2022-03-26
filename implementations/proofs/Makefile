# Part of pkmath package
# author Antonio AKA Lord Feistel

OBJS	= crypto_math.o demo.o tests.o
SOURCE	= crypto_math.cpp demo.cpp tests.cpp
HEADER	= 
OUT		= demo
CC	 	= g++
FLAGS	= -g -c -Wall -std=c++17
LFLAGS	= 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

euclidean.o: crypto_math.cpp
	$(CC) $(FLAGS) crypto_math.cpp 

teste.o: teste.cpp
	$(CC) $(FLAGS) tests.cpp 


clean:
	rm -f $(OBJS) $(OUT)
