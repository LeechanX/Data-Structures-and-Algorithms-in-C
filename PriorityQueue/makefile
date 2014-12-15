target=pg
$(target):main.o PriorityQueue.o PriorityQueue.h
	gcc -o pg main.o PriorityQueue.o
main.o:main.c PriorityQueue.h
	gcc -c main.c
PriorityQueue.o:PriorityQueue.c PriorityQueue.h
	gcc -c PriorityQueue.c
.PHONY:clean run
clean:
	-rm main.o PriorityQueue.o pg
run:
	./$(target)
