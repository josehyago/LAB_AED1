/*
* 1-) Considere listas encadeadas de valores inteiros e implemente uma 
* função para retornar o número de nós da lista que possuem o campo info com valores maiores do que n. 
* Essa função deve obedecer ao protótipo: int maiores(Lista* l, int n);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
} Lista;

int maiores(Lista *l, int n){
    int contador = 0;
    Lista *novo = l;
    while (novo != NULL){
        if(novo->info > n) contador++;
        novo = novo->prox;
    }
    return contador;
}

int main(){
    Lista *l = malloc(sizeof(Lista));
    Lista *l1 = malloc(sizeof(Lista));
    Lista *l2 = malloc(sizeof(Lista));
    Lista *l3 = malloc(sizeof(Lista));

    if (l == NULL || l1 == NULL || l2 == NULL || l3 == NULL){
        printf("Erro ao alocar memoria.\n");
        free(l);
        free(l1);
        free(l2);
        free(l3);
        return 1;
    }

    l->info = 0;
    l1->info = 1;
    l2->info = 2;
    l3->info = 3;
    l->prox = l1;
    l1->prox = l2;
    l2->prox = l3;
    l3->prox = NULL;
    printf("%d\n", maiores(l, 2));
    free(l3);
    free(l2);
    free(l1);
    free(l);
    return 0;
}