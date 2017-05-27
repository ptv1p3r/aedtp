#ifndef _ITEM_TYPE_
	
	#define _ITEM_TYPE_
	typedef struct s_item *ITEM;
#endif

/*
DES: devolve um novo item
EXC: aborta em caso de falha de alocação");
*/
ITEM create_item(int key, char value);

/*
DES: define a chave do item
*/
void set_item_key(ITEM i, int key);


/*
DES: defina o valor dos dados satélite do item
*/
void set_item_sat(ITEM i, char sat);

/*
DES: devolve a chave do item
*/
int get_item_key(ITEM i);


/*
DES: devolve o valor dos dados satélite do item
*/
char get_item_sat(ITEM i);
