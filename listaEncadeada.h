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
