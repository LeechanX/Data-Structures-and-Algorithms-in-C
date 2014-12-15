#ifndef BINARYTREE_H
#define BINARYTREE_H
#define STACKSIZE 300

struct BTree{
	int vertex;
	struct BTree *left;
	struct BTree *right;
};
typedef struct BTree *btlink;

void insert_btree(btlink *,int);
btlink insert_btree_recursive(btlink,int);
void delete_btree(btlink *,int);
btlink search_btree_recursive(btlink,int);
btlink search_btree_nonrecursive(btlink,int);
void prefix_recursive(btlink);
void infix_recursive(btlink);
void suffix_recursive(btlink);
void prefix_nonrecursive(btlink);
void infix_nonrecursive(btlink);
void suffix_nonrecursive(btlink);
void destroy_tree(btlink);
void bfs(btlink);

#endif