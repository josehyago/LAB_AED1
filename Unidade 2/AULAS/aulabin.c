#include <stdio.h>
#include <stdlib.h>

typedef struct aluno
{
    char nome [20];
    int mat;
}Aluno;

int main(){
    Aluno a = {"Samuel", 20250987};
    Aluno b;
    // FILE *arquivo = fopen("dados.dat", "wb");
    FILE *arquivo = fopen("dados.dat", "rb");
    if(arquivo == NULL){
        exit(1);
    }
    // fwrite(&a, sizeof(Aluno), 1, arquivo); // Escreve struct no arquivo 
    fread(&b, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);
    printf("Matricula: %d \n", b.mat);
    printf("Nome: %s", b.nome);
    
    return 0;
}