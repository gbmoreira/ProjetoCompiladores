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

#include<stdio.h>
#include<stdlib.h>
#include "listaEncadeada.h"


/* A função recebe um inteiro x e uma lista encadeada(com cabeça) e devolve
 * o dendereço de uma lista que contem x. Se não existir tal velula a
 * função devolve NULL */
lista *busca(int x, lista *ini){
 	lista *p = ini->prox;
	while(p!=NULL && p->conteudo != x){
		p = p->prox;
	}
	return p;
}

lista *busca_r(int x, lista *p){
 	if(p->prox==NULL)
	 	return NULL;
	if(p->prox->conteudo == x)
	 	return p->prox;
	return busca_r(x,p->prox);	
}

lista *nova(int x){
	lista *p = malloc(sizeof(lista));
	if(p==NULL){
		printf("ERRO: Memória insuficiente"); 
		exit(1);
	}
	p->conteudo=x;
	p->prox=NULL;
	return p;
}

void insere(int x, lista *p){
	lista *q = nova(x);
	q->prox=p->prox;
	p->prox=q;
}

/* A função recebe um endereço de uma lista p e remove da lista o elemento
 * p->prox */
void remove_lista(lista *p){
	lista *q = p->prox;
	p->prox = q->prox;
	free(q);
}

/* A função recebe um endereço da cabeça de uma lista e insere uma nova
 * lista com conteudo x no inicio da lista */
void insere_inicio(lista *ini, int x){
	insere(x, ini); 
}

/* A função recebe um endereço da cabeça de uma lista encadeada e insere uma nova
 * lista com conteudo x no fim da lista */
void insere_fim(lista *ini, int x){
	lista *u=ini->prox;
	if(u==NULL){
		insere(x, ini);
		return;
	}
	while(u->prox !=NULL){
		u=u->prox;
	}

	insere(x, u);
}

/* A função remove da lista com cabeça, a primeira lista. Se a lista
 * estiver vazia a função não faz nada */
void remove_inicio(lista *ini){
	if(ini->prox!=NULL){
		remove_lista(ini); 
	} 
}

/* A função remove a ultima lista da lista encadeada. Se a lista estiver
 * vazia a função não faz nada */
int remove_fim(lista *ini){
int numberToReturn = 0;	
    lista *p;
	if(ini->prox != NULL){
		p=ini;
		while(p->prox->prox != NULL){
			p=p->prox; 
		}
                numberToReturn = p->prox->conteudo;
				remove_lista(p);
    	}
     return numberToReturn;
  
}
int listIsEmpty(lista *ini)
{
    if(ini->prox == NULL)
        return 1;
    else
        return 0;
}


/*
	Este método esta no lugar errado, tem que estar em utils.c
*/
 short testarDoisUltimosElementos(lista *ini)
 {
 	printf("TEST\n");
    if (!listIsEmpty(ini))
    { 
    	 	printf("TEST2\n");
   lista *element1;
   lista *element2;

	if(ini->prox != NULL && ini->prox->prox !=NULL)
        {
        	    	 	printf("TEST3\n");
		element1=ini;
		while(element1->prox->prox->prox != NULL)
                {
                    element1=element1->prox; 
				}
				element2 = element1->prox->prox;
                element1 = element1->prox;
             //   if (element1->tipo == element2->tipo)
                    //return 1;
                //else 
                  //  return 0;
        }
    }
    printf("TEST4\n");
    return 0;
 }


void exibeLista(lista *ini){
		lista *t;

	for(t=ini->prox; t!=NULL; t=t->prox){
		printf("%d\n",t->conteudo);
	}
}
 	

/*int main(){
	lista ini;
	ini.prox=NULL;

	insere_fim(&ini,15);
	insere_fim(&ini,25);
	insere_fim(&ini,35);
	insere_fim(&ini,45);

	insere_inicio(&ini,7);
	insere_fim(&ini,1);
	remove_inicio(&ini);
	remove_fim(&ini);

	lista *t;
	for(t=ini.prox; t!=NULL; t=t->prox){
		printf("%d\n",t->conteudo);
	}

	return 0;	
}*/

