kruskal:main.o map.o heap.o disjointset.o
	gcc -o kruskal main.o map.o heap.o disjointset.o
main.o:main.c map.h disjointset.h heap.h
	gcc -c main.c
map.o:map.c map.h
	gcc -c map.c
heap.o:heap.c heap.h
	gcc -c heap.c
disjointset.o:disjointset.c disjointset.h
	gcc -c disjointset.c
.PHONY:clean run
clean:
	rm main.o map.o heap.o disjointset.o kruskal
run:
	./kruskal $(M)
