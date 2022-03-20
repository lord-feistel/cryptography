# Part of pkmath package
# author Antonio AKA Lord Feistel

OBJS	= crypto_math.o proof.o tests.o
SOURCE	= crypto_math.cpp proof.cpp tests.cpp
HEADER	= 
OUT		= proof
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
