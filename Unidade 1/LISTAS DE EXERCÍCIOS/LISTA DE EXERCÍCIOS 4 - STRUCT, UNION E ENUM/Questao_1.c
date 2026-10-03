// Escreva um programa que implementa uma struct Pessoa com os campos nome, idade e gênero. O gênero deve ser armazenado como um enum com os valores MASCULINO e FEMININO. O programa deve ler os dados de uma pessoa e imprimir os dados da pessoa.
#include <stdio.h>
#include <string.h>

typedef enum {
    MASCULINO = 1,
    FEMININO = 2
} Genero;

typedef struct{
    char nome[50];
    int idade;
    Genero g;
} Pessoa;

const char* exibir_genero(Genero g){
    switch (g)
    {
    case MASCULINO: return "Masculino";
    case FEMININO: return "Feminino";
    default: return "Invalido";
    }
} 

int main(){
    Pessoa pessoa;
    int genero_opcao;
    printf("Digite seu nome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    pessoa.nome[strcspn(pessoa.nome, "\n")] = '\0';
    printf("Digite sua idade: ");
    scanf("%d", &pessoa.idade);
    printf("Digite seu genero [1 M 2 F]: ");
    scanf("%d", &genero_opcao);
    pessoa.g = (Genero)genero_opcao;
    printf("Nome: %s | Idade: %d | Genero: %s\n", pessoa.nome, pessoa.idade, exibir_genero(pessoa.g));

    return 0;
}