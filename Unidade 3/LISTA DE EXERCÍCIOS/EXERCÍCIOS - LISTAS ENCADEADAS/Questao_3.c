/*
* Implemente uma função que receba duas listas encadeadas de valores reais e
* retorne a lista resultante da concatenação das duas listas recebidas como
* parâmetros, isto é, após a concatenação, o último elemento da primeira lista
* deve apontar para o primeiro elemento da segunda lista,
* Essa função deve obedecer ao protótipo: Lista* contatena(Lista* l1, Lista* l2);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    float info;
    struct lista *prox;
} Lista;

Lista* concatena(Lista* l1, Lista* l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    
    Lista *inicio = l1;
    
    while (l1->prox != NULL){
        l1 = l1->prox;
    }

    l1->prox = l2;
    return inicio;
}

int main(){
    Lista *l1 = malloc(sizeof(Lista));
    Lista *l2 = malloc(sizeof(Lista));
    Lista *l3 = malloc(sizeof(Lista));
    Lista *l4 = malloc(sizeof(Lista));

    if (l1 == NULL || l2 == NULL || l3 == NULL || l4 == NULL){
        printf("Erro ao alocar memoria.\n");
        free(l1);
        free(l2);
        free(l3);
        free(l4);
        return 1;
    }

    l1->info = 1.0;
    l2->info = 2.0;
    l3->info = 3.0;
    l4->info = 4.0;

    l1->prox = l2;
    l2->prox = NULL;

    l3->prox = l4;
    l4->prox = NULL;

    Lista *resultado = concatena(l1, l3);

    printf("Lista concatenada: ");
    while (resultado != NULL){
        printf("%.1f ", resultado->info);
        resultado = resultado->prox;
    }
    printf("\n");

    free(l4);
    free(l3);
    free(l2);
    free(l1);

    return 0;
}