treeconvert:main.o treeconvert.o
	gcc -o treeconvert main.o treeconvert.o
main.o:main.c treeconvert.h
	gcc -c main.c
treeconvert.o:treeconvert.c treeconvert.h
	gcc -c treeconvert.c
.PHONY:clean run
clean:
	-rm treeconvert main.o treeconvert.o
run:
	./treeconvert