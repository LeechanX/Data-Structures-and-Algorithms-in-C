#include <stdlib.h>
#include "binarytree.h"
#include "reverseisotree.h"

btlink reverse_btree_iso(btlink btree){
	if(!btree)
		return NULL;
	btlink tmpleft=btree->left,tmpright=btree->right;
	btree->left=reverse_btree_iso(tmpright);
	btree->right=reverse_btree_iso(tmpleft);
	return btree;
}