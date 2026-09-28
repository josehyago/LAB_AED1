/* Implemente um programa em C para ler o nome e as notas de um número N de alunos e armazená-los em um arquivo.*/

#include <stdio.h>

typedef struct{
    char nome[20];
    float n1;
    float n2;
    float n3;
} Estudantes;

int main(){
    int n, i;
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &n);
    Estudantes e[n];
    for(i = 0; i < n; i++){
        printf("Digite o nome e as notas do aluno %d: ", i + 1);
        scanf("%s %f %f %f", e[i].nome, &e[i].n1, &e[i].n2, &e[i].n3);
    }
    FILE *file = fopen("./alunos.txt", "w");
    for(i = 0; i < n; i++){
    fprintf(file, "Nome: %s | Notas: %.2f %.2f %.2f\n", e[i].nome, e[i].n1, e[i].n2, e[i].n3);
    }
    fclose(file);
    return 0;
}