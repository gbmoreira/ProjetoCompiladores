/*+-------------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                    |
 | BACHARELADO EM CIENCIA DA COMPUTACAO.                        |
 | Atividade.: 1                                                |
 | Disciplina: Compiladores                                     |
 | Professor.: Luiz Eduardo da Silva                            |
 | Aluno(s)..: Gabriela Moreira da Silva - 2011.1.08.038        |
 | Jesper Bolling - 2014.1.08.039                               |
 | Data......: 07/12/2014                                       |
 +-------------------------------------------------------------+*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

/*+-----------------------------------------+
  |		ESTRUTURA DA TABELA HASH			|
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

/*+-----------------------------------------+
  |		FUNCOES DA TABELA HASH	  			|
  +-----------------------------------------+
*/

hash_table_t* hash_create(int size);
unsigned int hash_function(hash_table_t *hashTable, char *str);
list_t* hash_get(hash_table_t *hashTable, char *str);
int hash_set(hash_table_t *hashTable, char *str, int deslocamento, int tipo);
#endif