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
 
#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H


/*+-----------------------------------------+
  |		ESTRUTURA DA LISTA ENCADEADA		|
  +-----------------------------------------+
*/


typedef struct lista lista;

struct lista{
		int conteudo; // conteudo pode ser tipo, rotulo ou deslocamento
	    lista *prox;
};

lista *busca(int x, lista *ini);
lista *busca_r(int x, lista *p);
lista *nova(int x);
void insere(int x, lista *p);
void remove_lista(lista *p);
void insere_inicio(lista *ini, int x);
void insere_fim(lista *ini, int x);
void remove_inicio(lista *ini);
int remove_fim(lista *ini);
int listIsEmpty(lista *ini);
short testarDoisUltimosElementos(lista *ini);
void exibeLista(lista *ini);
#endif
