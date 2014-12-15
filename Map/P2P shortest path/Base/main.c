#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "map.h"

int **getnextmatrix(int **matrix,int nodesize,int **map){
	int **nextmatrix=malloc(sizeof(int *)*nodesize);
	for(int i=0;i<nodesize;i++){
		nextmatrix[i]=malloc(sizeof(int)*nodesize);
		for(int j=0;j<nodesize;j++){
			nextmatrix[i][j]=SHRT_MAX;
			for(int k=0;k<nodesize;k++)
				if(nextmatrix[i][j]>matrix[i][k]+map[k][j])
					nextmatrix[i][j]=matrix[i][k]+map[k][j];
		}
	}
	return nextmatrix;
}

void basemethod(int **map,int nodesize){
	for(int i=0;i<nodesize;i++)
		for(int j=0;j<nodesize;j++)
			if(i!=j && !map[i][j])
				map[i][j]=SHRT_MAX;
	int **nextmatrix=map;
	int i=1;
	while(i<nodesize-1){
		nextmatrix=getnextmatrix(nextmatrix,nodesize,nextmatrix);
		i*=2;
	}
	display_debug(nextmatrix,nodesize);
	//for(int i=2;i<=nodesize-1;i++)
	//	nextmatrix=getnextmatrix(nextmatrix,nodesize,map);
	//display_debug(nextmatrix,nodesize);
}

int main(int argc, char const *argv[])
{
	if(argc<2)
		return 1;
	int nodesize;
	int **map=read_map(argv[1],&nodesize);
	//display_debug(map,nodesize);
	basemethod(map,nodesize);
	return 0;
}