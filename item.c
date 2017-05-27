#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct s_item {
	int key; /* poderíamos/deveríamos definir tipo para chave */
	char value;
};


/*
DES: devolve um novo item
EXC: aborta em caso de falha de alocação");
*/
ITEM create_item(int key, char value) {
	ITEM i = (ITEM)malloc(sizeof(*i));
	if (!i) {
		fprintf(stdout, "Memmory allocation error!\n");
		exit(1);
	}

	i->key = key;
	i->value = value;
	
	return i;
}

/*
DES: define a chave do item
*/
void set_item_key(ITEM i, int key) {
	i->key = key;
}


/*
DES: define o valor dos dados satélite do item
*/
void set_item_sat(ITEM i, char sat) {
	i->value = sat;
}

/*
DES: devolve a chave do item
*/
int get_item_key(ITEM i) {
	return i->key;
}


/*
DES: devolve o valor dos dados satélite do item
*/
char get_item_sat(ITEM i) {
	return i->value;
}
