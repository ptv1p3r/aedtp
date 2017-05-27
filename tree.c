
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct t_node
{
	TREE left;
	TREE right;
	ITEM item;
};


TREE create_node(ITEM item)
{
	TREE node = (TREE)malloc(sizeof(TREE));
	if (!node) {
		fprintf(stdout, "Memmory allocation error!\n");
		exit(1);
	}

	node-> left = NULL;
	node-> right = NULL;
	node-> item = item;

	return node;
}


void insert_left(TREE parent, TREE son)
{
	parent->left = son;
}

void insert_right(TREE parent, TREE son)
{
	parent->right = son;
}

void insert(TREE parent, TREE left_son, TREE right_son)
{
	parent->left = left_son;
	parent->right = right_son;
}

TREE get_left(TREE parent)
{
	return parent->left;
}

TREE get_right(TREE parent)
{
	return parent->right;
}

ITEM get_item(TREE node)
{
	return node->item;
}

void print_tree(TREE tree)
{
	if(tree != NULL)
	{
		printf("%c\n", get_item_sat(tree->item));
		print_tree(tree->left);
		print_tree(tree->right);

	}
}

/**
 * Metodo que imprime o caminho mais longo de uma tree desde a root ate a leaf inclusive
 * @param tree Arvore binaria
 * @param path Array que guarda o caminho na tree
 * @param len Valor que indica o index
 * @param depth Tamanho da tree
 */
void printLongestPath(TREE tree, int* path, int len, int depth){

    if (tree == NULL) return;

    path[len] = get_item_sat(tree->item);               // valor para o path

    len++;
    depth--;

    if ( depth == -1 ) {                                // max depth da root to leaf
        printPath(path, len);
        return;
    }

    printLongestPath(tree->left, path, len, depth);     // percorre a esquerda recursivamente
    printLongestPath(tree->right, path, len, depth);    // percorre a direita recursivamente
}

void printPath(int* path, int len) {
    int i;
    for ( i = 0; i < len; i++ ){
        if (i!=0) printf("->");
        printf("%c",path[i]);
    }
}


int get_tree_height(TREE tree)
{	int left_height = 0;
	int right_height = 0;
	if( tree != NULL)
	{	if(tree->left) left_height = 1;
		if(tree->right) right_height = 1;
		left_height += get_tree_height(tree->left);
		right_height += get_tree_height(tree->right);
	}

	return (left_height > right_height?left_height:right_height);

}

void delete_tree(TREE a){;}

