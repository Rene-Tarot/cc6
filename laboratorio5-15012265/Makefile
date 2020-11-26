all: 
	gcc -pthread createThread.c -o createThread.o
	gcc -pthread joinThread.c -o joinThread.o
	gcc -pthread mutexThread.c -o mutexThread.o
	gcc -pthread conditionThread.c -o conditionThread.o

brige:
	gcc -pthread brige.c -o brige.o && ./brige.o

clean: 
	rm -f *.o
