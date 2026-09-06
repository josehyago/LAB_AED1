//Crie um programa em C que leia um núumero inteiro positivo n do usuário e aloque dinamicamente memória para armazenar uma matriz quadrada de ordem n. Preencha essa matriz com números aleatórios entre 1 e 100, e em seguida, exiba a matriz resultante.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n, il, ic;
    printf("Informe um numero para a matriz quadrada de ordem n: ");
    scanf("%d", &n);

    int **matriz = (int **) malloc(n * sizeof(int *));
    if (matriz == NULL){
        printf("Nao ha memoria suficiente para as linhas. Insira outro valor");
        exit (1);
    }
    for(int i = 0; i < n; i++){
        matriz[i] = (int *) malloc(n * sizeof(int));
        
        if (matriz[i] == NULL){
            printf("Nao ha memoria suficiente para as colunas");
            exit (1);
        }
}

    srand(time(NULL));

    for(il = 0; il < n; il++){
        for(ic = 0; ic < n; ic++){
            matriz[il][ic] = (rand() % 100) + 1;
        }
    } 

    printf("Matriz Resultante de ordem %d:\n", n);
    for(il = 0; il < n; il++){
        for(ic = 0; ic < n; ic++){
            printf("[%d] ", matriz[il][ic]);
        }
        printf("\n");
    }


    return 0;
}