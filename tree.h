#include <stdlib.h>
#include <stdio.h>
#include "treeType.h"

#ifndef _TREE_TYPE
typedef struct t_node *TREE;
#endif

TREE create_node(ITEM item);

void insert_left(TREE parent, TREE son);
void insert_right(TREE parent, TREE son);
void insert(TREE parent, TREE left, TREE right);
TREE get_left(TREE parent);
TREE get_right(TREE parent);

ITEM get_item(TREE node);
int get_tree_height(TREE tree);

void printLongestPath(TREE tree, int* path,int len,int depth);

void print_tree(TREE tree);

void delete_tree(TREE a);
