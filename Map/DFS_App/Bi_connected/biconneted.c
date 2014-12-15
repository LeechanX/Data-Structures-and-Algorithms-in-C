#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void create_dfstree(struct Graph *map,){}

int main(int argc, char const *argv[]){
	if(argc<2)
		return 1;
	struct Graph *map=read_map(argv[1]);
	//display_debug(map);
	//draw(map);
	return 0;
}