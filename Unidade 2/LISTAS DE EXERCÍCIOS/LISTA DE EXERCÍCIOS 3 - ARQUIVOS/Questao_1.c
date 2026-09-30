/* Crie um programa em C para armazenar alunos em um arquivo binário alunos.dat. Cada aluno
possui matrícula, nome, curso e média. Implemente as operações de cadastro, listagem, busca por
matrícula e alteração da média. Determine a complexidade de cada operação em função de n alunos.
*/

#include <stdio.h>
#include <string.h>

typedef struct alunos{
    int matricula;
    char nome[30];
    char curso[30];
    float media;
} Alunos;

int main(){
    FILE *file = fopen("./alunos.dat", "wb");
    if (file == NULL){
        return 1;
    }
    Alunos a;
    int escolha;
    char nomealuno[30];
    char nomecurso[30];
    do{
    printf("Menu de Cadastro de Aluno:\n");
    printf("1 - Cadastrar\n");
    printf("2 - Parar\n");
    printf("Escolha a opcao:");
    scanf("%d", &escolha);
    switch (escolha){
    case 1:
    printf("Digite a matricula do aluno: ");
    scanf("%d", &a.matricula);
    getchar();
    printf("Digite o nome do aluno: ");
    fgets(nomealuno, sizeof(nomealuno), stdin);
    nomealuno[strcspn(nomealuno, "\n")] = '\0';
    strcpy(nomealuno, a.nome);
    printf("Digite o nome do curso: ");
     fgets(nomecurso, sizeof(nomecurso), stdin);
    nomecurso[strcspn(nomecurso, "\n")] = '\0';
    strcpy(nomecurso, a.curso);
    printf("Digite a media do aluno: ");
    scanf("%f", &a.media);
    getchar();
    fwrite(&a, sizeof(Alunos), 1, file);
        break;
    case 2:
    printf("Encerrando o sistema.");
    break;    
    default:
    printf("Opcao invalida.");
        break;
    }
    }while (escolha != 2);
    fclose(file);
        return 0;
}