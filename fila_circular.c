#include <stdio.h>
#include <stdlib.h>

# define MAX 10;

typedef struct{
	int itens[MAX];
	int com,tam,fim;
}fila;

void iniciaFila(fila*F){
	F->tam=0;
	F->com=3;
	F->fim=2;
}

int insereNaFila(fila*F, int v){
	if(F->tam==MAX)
		return 0; /*Fila Cheia*/
	else{
		F-> tam++;
		F-> fim=(F->fim+1)%MAX;
		F-> itens[F->fim]=v;
		return 1;
	}

}

int retiraDaFila(fila*F,int *v){
	if(F->tam==0);
		return 0;
	else{
		F-> tam--;
		*v = F->itens[F->com];
		F-> fim(F->fim+1)%MAX;
		return 1;
	}
}

/* Programa Principal */

main (){
	fila A;
	int num, ok;
	iniciaFila(&A);
	
	do{
		scanf("%d",&num);	
		ok = insereNaFila(&A,num);
		
		if(ok)
			puts("Insercao OK !");
		else
			puts("Fila Cheia");
	}while(num);

	while(retiraDaFila(&A,&num))
		printf("%d",num);
}
