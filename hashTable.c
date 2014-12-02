#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
//#include "hashTable.h"

/*+-----------------------------------------+
  |     ESTRUTURA DA TABELA HASH            |
  +-----------------------------------------+
*/

//elemento
struct _list_t_ {
    char *identificador;
    int deslocamento;
    int tipo;
    struct _list_t_ *next;
};
 
typedef struct _list_t_ list_t;
 
 //tabela
struct _hash_table_t_ {
    int size;
    struct _list_t_ **table;    
};
 
typedef struct _hash_table_t_ hash_table_t;

/* Funcao para criar a hash, retorna uma hash. */
hash_table_t* hash_create(int size){

	hash_table_t *new_table;

	//Tamanho invalido para a tabela
	if(size < 1) return NULL;
    
    //Tentativa alocar a memoria
    if ((new_table = malloc(sizeof(new_table))) == NULL) {
        return NULL;
    }

    //Tentativa de alocar a memoria para a propria tabela
    if((new_table->table = malloc(sizeof(list_t*)*size))==NULL){
    	return NULL;
    }

    int i;
    //Iniciando os elementos da tabela
    for (i = 0; i < size; i++)
    {
    	new_table->table[i]==NULL;
    	new_table->size = size;
    }

    return new_table;
}

/* Funcao para funcao de espalhamento */
//unsigned para garantir que nunca ira receber um valor negativo.
unsigned int hash_function(hash_table_t *hashTable, char *str){

	unsigned int hashValue;

	/* we start our hash out at 0 */
    hashValue = 0;

    /* 
	 * Multiplica o hashValue por 2^5 
     * 
     * for each character, we multiply the old hash by 31 and add the current
     * character.  Remember that shifting a number left is equivalent to 
     * multiplying it by 2 raised to the number of places shifted.  So we 
     * are in effect multiplying hashValue by 32 and then subtracting hashValue.  
     * Why do we do this?  Because shifting and subtraction are much more 
     * efficient operations than multiplication.
     */
    for(; *str != '\0'; str++) hashValue = *str + (hashValue << 5) - hashValue;

    /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
    return hashValue % hashTable->size;

}

/* Funcao para buscar na tabela hash.
 *
 * No trabalho eh necessario retornar tanto o DESLOCAMENTO, quanto
 * o tipo, depende de onde for chamado no sintatico.y
 * Para isso criei um campo onde sera informado o que ele deseja
 *  que retorne -  
*/
list_t* hash_get(hash_table_t *hashTable, char *str)
{
    list_t *list;
    unsigned int hashValue = hash_function(hashTable, str);

    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL.
     */
        // printf("INDICE %d\n",hashValue ); 

    for(list = hashTable->table[hashValue]; list != NULL; list = list->next) {
        if (strcmp(str, list->identificador) == 0) return list;

    }

    return NULL;
}



/* Funcao para inserir na tabela hash. 
*/
int hash_set(hash_table_t *hashTable, char *str, int deslocamento, int tipo){

	unsigned int hashValue = hash_function(hashTable,str);
	list_t *new_list;
	list_t *current_list;

	//Tentativa de alocar na memoria
	if((new_list = malloc(sizeof(list_t)))==NULL) return 1;

	//Se o elemento ja existe...
    current_list = hash_get(hashTable, str);
    /* item already exists, don't insert it again. */
    if (current_list != NULL) return ;
    /* Insert into list */
    new_list->identificador = strdup(str);
    new_list->deslocamento = deslocamento;
    new_list->tipo = tipo;
    //printf("IDENTIFICADOR: %s\n",new_list->identificador);
    //printf("TIPO: %d\n",new_list->tipo);
    //printf("DESLOCAMENTO: %d\n\n", new_list->deslocamento);
    new_list->next = hashTable->table[hashValue];
    hashTable->table[hashValue] = new_list;

    return 0;}

/*
int main( int argc, char **argv ) {
 	int size_of_table = 25000;
 	hash_table_t *my_table;
 	my_table = hash_create(size_of_table);
	hash_set(my_table, "Gabi", 5, 1);
  hash_set(my_table, "Gabizinha", 0,0);
    
    
	//printf("retorno da funcao %s\n",retorno ); 



  list_t *current_list;

  //Tentativa de alocar na memoria

  //Se o elemento ja existe...
    current_list = hash_get(my_table, "Gabi");
    printf("IDENTIFICADOR: %s\n",current_list->identificador);
    printf("TIPO: %d\n",current_list->tipo);
    printf("DESLOCAMENTO: %d\n\n", current_list->deslocamento);



	return 0;
}*/