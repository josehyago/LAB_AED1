// Escreva um programa em C que solicite ao usuário o tamanho de um vetor e, em seguida, aloque dinamicamente memória para armazenar esse vetor. Depois disso, peça ao usuário que insira os elementos do vetor e, por fim, imprima os elementos na ordem inversa.

#include <stdio.h>
#include <stdlib.h> // malloc , calloc, free, realloc

int main(void){

    int n;
    scanf("%d", &n);

    //int vetor[n];
    int * vetor = (int *) malloc(n*sizeof(int));
    if(vetor == NULL){
        printf("Nao ha memoria\n");
        exit(1);
    }
    else{
        printf("Alocacao realizada!\n");
    }
    printf("Digite os valores: \n");
    int index;
    for(index = 0; index < n; index++){
        scanf("%d", &vetor[index]);
    }

    for(index = n - 1; index >= 0; index--){
        printf("%d ", vetor[index]);
    }

    return 0;
}