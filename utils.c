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

/*---------------------------------------------------------
 *  Limites das estruturas
 *--------------------------------------------------------*/

#include<stdarg.h>
#include<string.h>
#include "hashTable.h"
#include "listaEncadeada.h"

/*---------------------------------------------------------
 *  Variaveis globais
 *--------------------------------------------------------*/
int TAM_HASH = 30000; /* TOPO da tabela de simbolos */
int ROTULO = 0; /* Proximo numero de rotulo */
int CONTA_VARS = 0; /* Numero de variaveis */
int DESLOCA;
int TIPO;
int aux; /* variavel auxiliar */
int numLinha = 0; /* numero da linha no programa */
char atomo[30]; /* nome de um identif. ou numero */
typedef enum { INTEIRO, LOGICO} Tipo; 
Tipo tipo;

/*---------------------------------------------------------
 *  Rotina geral de tratamento de erro
 *--------------------------------------------------------*/
void ERRO(char *msg, ...) {
    char formato [255];
    va_list arg;
    va_start(arg, msg);
    sprintf(formato, "\n%d: ", numLinha);
    strcat(formato, msg);
    strcat(formato, "\n\n");
    printf("\nERRO no programa");
    vprintf(formato, arg);
    va_end(arg);
    exit(1);

}

/*---------------------------------------------------------
 *  Pilha Semantica
 *--------------------------------------------------------*/
lista pilhaSem;

/*---------------------------------------------------------
 *  Tabela de Simbolos
 *--------------------------------------------------------*/
hash_table_t *my_table;

/*---------------------------------------------------------
 * Funcao que BUSCA um simbolo na tabela de simbolos.       
 *  Caso exista na tabela de simbolos:    
 *      Retorna o deslocamento ou tipo da variavel.        
 *      Isso eh passado por parametro:
 *              'D' para deslocamento 
 *              'T' para tipo
 *                  
 *--------------------------------------------------------*/

int busca_simbolo_hash(char *ident, char tipo_desloca){

    list_t *current_list;
    current_list = hash_get(my_table, ident);
    if(current_list==NULL){
        return -1;
    }
    if(tipo_desloca == 'T'){
        return current_list->tipo;
    }else{
        return current_list->deslocamento;    
    }
    
    printf("\n");
}

/*---------------------------------------------------------
 * Rotinas para manutencao da PILHA SEMANTICA              
 *--------------------------------------------------------*/
void empilha(int n) {
    insere_fim(&pilhaSem, n);
}

int desempilha() {
    if (!listIsEmpty(&pilhaSem)){
        //exibeLista(&pilhaSem);
        return remove_fim(&pilhaSem);
    }else {
        ERRO("UNDERFLOW - Pilha Semantica");
    }


}

void existeSimbolo( char *ident, int inseriu){
    if(inseriu == -1){
        ERRO("Identificador [%s] duplicado", ident);
    }
}

/*---------------------------------------------------------
 * Funcao que inicializa a tabela hash
 *--------------------------------------------------------*/
void inicializa(){
    my_table = hash_create(TAM_HASH);
}

/*---------------------------------------------------------
 * Funcao verifica se os dois ultimos valores da pilha        
 *  sao iguais, se forem, empilha o valor INTEIRO.                   
 * Caso forem difentes o erro de imcompatibilidades de tipos
 * eh exibido.
 *--------------------------------------------------------*/
void tipos_compatives_inteiros(){

        int inteiro1 = desempilha();
        int inteiro2 = desempilha();

        if(inteiro1 == inteiro2){
             empilha(INTEIRO);
        }else
            ERRO("Tipos incompativeis!");          
}    

/*---------------------------------------------------------
 * Funcao verifica se os dois ultimos valores da pilha        
 *  sao iguais, se forem, empilha o valor LOGICO.
 * Caso forem difentes o erro de imcompatibilidades de tipos
 * eh exibido.                 
 *--------------------------------------------------------*/
void tipos_compatives_logicos(){

        int logico1 = desempilha();
        int logico2 = desempilha();

        if(logico1 == logico2){
             empilha(LOGICO);
        }else
            ERRO("Tipos incompativeis!");          
}   



   


