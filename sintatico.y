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
 
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils.c"
#include "lexico.c"
%}

// Simbolo de partida
%start programa

// Simbolos terminais
%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_IDENTIF
%token T_LEIA
%token T_ESCREVA
%token T_ENQTO
%token T_FACA
%token T_FIMENQTO
%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE
%token T_ATRIB
%token T_VEZES
%token T_DIV
%token T_MAIS
%token T_MENOS
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_E
%token T_OU
%token T_V
%token T_F
%token T_NUMERO
%token T_NAO
%token T_ABRE
%token T_FECHA
%token T_LOGICO
%token T_INTEIRO

// Precedencia e associatividade
%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV

%%

// Regras de producao
programa
      : cabecalho
      { 
        printf ("\tINPP\n");
        inicializa(); //Cria hash
        CONTA_VARS = 0;
      }  
        
        variaveis
      { printf ("\tAMEM\t%d\n", CONTA_VARS);}
        
        T_INICIO lista_comandos 
      { printf ("\tDMEM\t%d\n", CONTA_VARS);}
        
        T_FIM
      { printf ("\tFIMP\n"); }
      ;

cabecalho
      : T_PROGRAMA T_IDENTIF 
      ;

variaveis
      :  /* vazio */
      |  declaracao_variaveis 
      ;

declaracao_variaveis
      : declaracao_variaveis
        tipo 
        lista_variaveis 

      | tipo 
        lista_variaveis
      ;

tipo
      : T_LOGICO
        { 
          tipo = LOGICO;        
          empilha (tipo); //Item 3 do pdf - OK
        }
      
      | T_INTEIRO 
        { 
          tipo = INTEIRO;
          empilha (tipo); //Item 2 do pdf - OK
        }
      ;

lista_variaveis
      : lista_variaveis 
        T_IDENTIF 
          {   
              int tipo = desempilha();
              empilha(tipo); 
              int inseriu = hash_set(my_table, atomo, CONTA_VARS, tipo);
              existeSimbolo(atomo, inseriu);
              CONTA_VARS++;
          }

      | T_IDENTIF
          {  
            int tipo = desempilha();
            empilha(tipo); 
            int inseriu = hash_set(my_table, atomo, CONTA_VARS, tipo);
            existeSimbolo(atomo, inseriu);
            CONTA_VARS++;
          }

      ;

lista_comandos
      : /* vazio */
      | comando lista_comandos
      ;

comando
      : entrada_saida
      | repeticao
      | selecao
      | atribuicao
      ;

entrada_saida
      : leitura
      | escrita
      ;

leitura
      : T_LEIA  
        T_IDENTIF 
          { 
            DESLOCA = busca_simbolo_hash(atomo,'D');
            if(DESLOCA==-1){
                ERRO ("Variavel [%s] nao declarada!", atomo);
            }else{
                printf ("\tLEIA\n");
                printf ("\tARZG\t%d\n", DESLOCA);
            }

          }
      ;

escrita
      : T_ESCREVA expressao
          { printf ("\tESCR\n"); }
      ;

repeticao
      : T_ENQTO
           {
             TIPO = desempilha();
             if(TIPO==1){ // se for logico
                printf ("L%d\tNADA\n", ++ROTULO);
                empilha (ROTULO);
             }else{ //se for
                ERRO("Condicao precisa ser do tipo logico!");
             }  
           } 
        expressao 
        T_FACA 
           {
             printf ("\tDSVF\tL%d\n",++ROTULO);
             empilha (ROTULO);
           }
        lista_comandos 
        T_FIMENQTO
           {
             aux = desempilha();
             printf ("\tDSVS\tL%d\n", desempilha()); 
             printf ("L%d\tNADA\n", aux);           
           }
      ;

selecao
      : T_SE 
        expressao 
           {

             TIPO = desempilha();
             if(TIPO==1){
                printf ("\tDSVF\tL%d\n", ++ROTULO); 
                empilha (ROTULO);
             }else{
                ERRO("Condicao precisa ser do tipo logico!");
             } 
             
           }  
        T_ENTAO 
        lista_comandos 
        T_SENAO 
           {
             printf ("\tDSVS\tL%d\n", ++ROTULO);
             printf ("L%d\tNADA\n", desempilha()); 
             empilha (ROTULO);
           }
        lista_comandos 
        T_FIMSE
           {
             printf ("L%d\tNADA\n", desempilha());    
           }
      ;

atribuicao
      : T_IDENTIF 
          { 
            DESLOCA = busca_simbolo_hash(atomo,'D');
            TIPO = busca_simbolo_hash(atomo,'T');
            if(DESLOCA==-1){
                ERRO ("Variavel [%s] nao declarada!", atomo);
            }else{
                empilha(DESLOCA);
                empilha(TIPO);
            }
          }

        T_ATRIB 
        expressao
          { 

            int tipo1 = desempilha();
            int tipo2 = desempilha();
            if(tipo1!=tipo2){
              ERRO("Atribuicao com tipos incompativeis!");
            }
            printf ("\tARZG\t%d\n", desempilha()); 
          }
      ;

expressao
      : 
       expressao T_VEZES expressao 
          {   
           tipos_compatives_inteiros();
           printf ("\tMULT\n"); }
      
      | expressao T_DIV expressao
          {         
            tipos_compatives_inteiros();
            printf ("\tDIVI\n"); }

      | expressao T_MAIS expressao
          {  
            tipos_compatives_inteiros();
            printf ("\tSOMA\n"); }

      | expressao T_MENOS expressao
          {  
            tipos_compatives_inteiros();
            printf ("\tSUBT\n"); }

      | expressao T_MAIOR expressao
          { 
            tipos_compatives_logicos();       
            printf ("\tCMMA\n"); }
      | expressao T_MENOR expressao
          {         
            tipos_compatives_logicos();       
            printf ("\tCMME\n"); }
      | expressao T_IGUAL expressao
          {         
            tipos_compatives_logicos();       
            printf ("\tCMIG\n"); }
      | expressao T_E expressao
          {        
            tipos_compatives_logicos();       
            printf ("\tCONJ\n"); }
      | expressao T_OU expressao
          {        
            tipos_compatives_logicos();       
            printf ("\tDISJ\n"); }
      | termo
        
      ;

termo
      : T_IDENTIF
          {

            DESLOCA = busca_simbolo_hash(atomo, 'D');
            TIPO = busca_simbolo_hash(atomo, 'T');
            if(DESLOCA==-1){
                ERRO ("Variavel [%s] nao declarada!", atomo);
            }else{
                  printf ("\tCRVG\t%d\n", DESLOCA);
                  
                  if(TIPO){
                      empilha(LOGICO);
                  }else{
                      empilha(INTEIRO);
                  }
            }
          }
      | T_NUMERO
          { printf ("\tCRCT\t%s\n", atomo);
            empilha(INTEIRO); } 
      | T_V
          { printf ("\tCRCT\t1\n");
            empilha(LOGICO); } 
      | T_F
          { printf ("\tCRCT\t0\n");
            empilha(LOGICO); } 
      | T_NAO termo
          { printf ("\tNEGA\n"); 
            empilha(LOGICO); }
      | T_ABRE expressao T_FECHA
      ;

%%
/*+--------------------------------------------------------+
  |          Corpo principal do programa COMPILADOR        |
  +--------------------------------------------------------+*/

yywrap () {
}

yyerror (char *s)
{
  ERRO ("ERRO SINTATICO");
}

main ()
{
  yyparse ();
}
