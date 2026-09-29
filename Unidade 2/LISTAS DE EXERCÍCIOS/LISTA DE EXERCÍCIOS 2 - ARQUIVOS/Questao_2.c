/*Escreva um programa em C que preencha um vetor de 10 inteiros com informações
vindas de um arquivo e escreva em outro arquivo o menor elemento, o maior elemento, bem
como a média dos elementos do vetor, como ilustrado a seguir. */

#include <stdio.h>

int main() {
    FILE *entrada = fopen("./entrada_q2.txt", "r");
    FILE *saida = fopen("./saida_q2.txt", "w");
    
    if (entrada == NULL || saida == NULL){
        printf("Erro ao abrir os ficheiros.\n");
        return 1;
    }
    
    int vetor[10];
    int menor, maior;
    float media = 0.0;
    
    for (int i = 0; i < 10; i++){
        // Lê diretamente do ficheiro de entrada
        if (fscanf(entrada, "%d", &vetor[i]) != 1){
            printf("Erro: Ficheiro de entrada não contém 10 inteiros válidos.\n");
            fclose(entrada);
            fclose(saida);
            return 1;
        }
        
        if (i == 0){
            menor = vetor[i];
            maior = vetor[i];
        } else {
            if (vetor[i] < menor){
                menor = vetor[i];
            }
            if (vetor[i] > maior){
                maior = vetor[i];
            }
        }
        media += vetor[i];
    }
    
    media /= 10.0;

    fprintf(saida, "menor elemento: %d\n", menor);
    fprintf(saida, "maior elemento: %d\n", maior);
    fprintf(saida, "media dos elementos: %f\n", media);

    fclose(entrada);
    fclose(saida);

    return 0;
}