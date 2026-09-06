// Implemente um programa em C que solicite ao usuário o número de linhas e colunas de uma matriz e, em seguida, aloque dinamicamente memória para armazenar essa matriz. Peça ao usuário que insira os elementos da matriz e, por fim, imprima a matriz na forma original e transposta.
#include <stdio.h>
#include <stdlib.h>

int main(){
int linhas, colunas, il, ic;

printf("Digite a quantidade de linhas e colunas da matriz: ");
scanf("%d %d", &linhas, &colunas);

int **matriz = (int **) malloc(linhas * sizeof(int *));
    if (matriz == NULL){
        printf("Nao ha memoria suficiente para as linhas. Insira outro valor");
        exit (1);
    }
    for(int i = 0; i < linhas; i++){
        matriz[i] = (int *) malloc(colunas * sizeof(int));
        
        if (matriz[i] == NULL){
            printf("Nao ha memoria suficiente para as colunas");
            exit (1);
        }
}

printf("Insira os valores da matriz: ");
for(il = 0; il < linhas; il++){
    for(ic = 0; ic < colunas; ic++){
    scanf("%d", &matriz[il][ic]);
    }
}
printf("Matriz original: \n");
for(il = 0; il < linhas; il++){
    for(ic = 0; ic < colunas; ic++){
        printf("[%d] ", matriz[il][ic]);
    }
    printf("\n");
}
printf("Matriz transposta: \n");
for(ic = 0; ic < colunas; ic++){
    for(il = 0; il < linhas; il++){
        printf("[%d] ", matriz[il][ic]);
    }
    printf("\n");
}

    return 0;
}