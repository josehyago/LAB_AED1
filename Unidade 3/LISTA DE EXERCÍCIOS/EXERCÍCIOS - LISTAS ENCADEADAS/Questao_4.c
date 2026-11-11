/* 
* Considere listas de valores inteiros e implemente uma função que receba como
* parâmetros uma lista encadeada e um valor inteiro n, retire da lista todas as
* ocorrências de n e retorne a lista resultante. Essa função deve obedecer ao
* protótipo: Lista* retira_n(Lista* l, int n);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
} Lista;

Lista* retira_n(Lista* l, int n){
    
}