/* 
* 2 -) Implemente uma função que tenha como valor de retorno o ponteiro para o
* último nó de uma lista encadeada. Essa função deve obedecer ao protótipo:
* Lista* ultimo(Lista* l);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
} Lista;

Lista* ultimo(Lista* l){
    if (l == NULL){
        return NULL;
    }

    while (l->prox != NULL){
        l = l->prox;
    }
    return l;
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

    Lista *ultimoNo = ultimo(l);
    printf("Ultimo no: %d\n", ultimoNo->info);

    free(l3);
    free(l2);
    free(l1);
    free(l);

    return 0;
}