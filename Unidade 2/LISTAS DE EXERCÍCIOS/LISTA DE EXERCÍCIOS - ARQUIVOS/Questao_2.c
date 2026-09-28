/* Implemente um programa em C para ler o nome e as notas de um número N de alunos e armazená-los em um arquivo.*/

#include <stdio.h>

typedef struct{
    char nome[50];
    float n1;
    float n2;
    float n3;
} Estudantes;

int main(){
    int n, i;

    printf("Digite a quantidade de alunos: ");

    if (scanf("%d", &n) != 1 || n <= 0){
        printf("Quantidade invalida. O programa sera encerrado.\n");
        return 1;
    }

    Estudantes e[n];

    for(i = 0; i < n; i++){
        printf("\nAluno %d\n", i + 1);
        printf("Nome do aluno: ");
        scanf(" %[^\n]", e[i].nome);
        
        printf("Digite as 3 notas: ");
        scanf("%f %f %f", &e[i].n1, &e[i].n2, &e[i].n3);
    }
    
    FILE *file = fopen("./alunos.txt", "w");
    
    if (file == NULL){
        printf("Erro ao criar o ficheiro\n");
        return 1;
    }

    for(i = 0; i < n; i++){
        fprintf(file, "Nome: %s | Notas: %.2f %.2f %.2f\n", e[i].nome, e[i].n1, e[i].n2, e[i].n3);
    }

    fclose(file);
    printf("\nOs dados dos %d alunos foram gravados em 'alunos.txt'.\n", n);
    return 0;
}