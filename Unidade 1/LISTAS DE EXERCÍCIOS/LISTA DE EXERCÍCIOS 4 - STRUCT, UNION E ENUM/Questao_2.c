// Escreva um programa que implementa uma struct Produto com os campos nome, preço e tipo. O tipo deve ser armazenado como uma union que armazena um dos tipos: ALIMENTO, BEBIDA ou ELETRONICO. O programa deve ler os dados de um produto e imprimir os dados do produto.
#include <stdio.h>
#include <string.h>

typedef enum{
    ALIMENTO = 1,
    BEBIDA = 2,
    ELETRONICO = 3
} Tipo_Enum;

typedef union{
    Tipo_Enum categoria;
} Tipo_Union;

typedef struct{
    char nome[50];
    float preco;
    Tipo_Union tipo;
} Produto;

const char * exibir_tipo(Tipo_Enum tipo){
    switch (tipo)
    {
    case ALIMENTO: return "Alimento";
    case BEBIDA: return "Bebida"; 
    case ELETRONICO: return "Eletronico";
    default: return "Invalido";
    }
}

int main(){
    Produto p;
    int tipo_opcao;
    printf("Digite o nome do produto: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);
    printf("Digite o tipo do produto [1 - ALIMENTO | 2 - BEBIDA | 3 - ELETRONICO]: ");
    scanf("%d", &tipo_opcao);
    p.tipo.categoria = (Tipo_Enum)tipo_opcao;

    printf("Dados do produto:\n nome: %s\n preco: %.2f\n tipo: %s\n", p.nome, p.preco, exibir_tipo(p.tipo.categoria));

    return 0;
}