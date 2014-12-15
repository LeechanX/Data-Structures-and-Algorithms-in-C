tree:main.o binarytree.o copybinarytree.o reverseisotree.o
	gcc -o tree main.o binarytree.o copybinarytree.o reverseisotree.o
main.o:main.c binarytree.h copybinarytree.h reverseisotree.h
	gcc -c main.c
binarytree.o:binarytree.h binarytree.c
	gcc -c binarytree.c
copybinarytree.o:copybinarytree.c copybinarytree.h binarytree.h
	gcc -c copybinarytree.c
reverseisotree.o:reverseisotree.c reverseisotree.h binarytree.h
	gcc -c reverseisotree.c
.PHONY:clean run
clean:
	-rm tree main.o binarytree.o copybinarytree.o reverseisotree.o
run:
	./tree