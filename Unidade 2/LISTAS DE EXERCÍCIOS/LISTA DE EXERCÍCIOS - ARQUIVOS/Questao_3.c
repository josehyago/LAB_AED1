/*Você foi contratado para desenvolver um programa em C que permita o cadastro de frutas e seus
preços em um arquivo de dados. O programa deve usar uma estrutura (struct) para armazenar os
detalhes de cada fruta, incluindo o nome da fruta e o preço.
O programa deve realizar as seguintes ações:
Definir uma estrutura chamada Fruta com os seguintes campos:
– nome (string) para armazenar o nome da fruta.
– preco (float) para armazenar o preço da fruta.
Permitir que o usuário insira os dados das frutas via teclado.
O usuário poderá cadastrar múltiplas frutas em uma única execução do programa. 
Para cada fruta, o programa deve solicitar:
O nome da fruta.
O preço da fruta.
Após inserir os dados de cada fruta, o programa deve salvar as informações no arquivo ”frutas.txt”.
Cada linha do arquivo deve conter o nome da fruta e seu preço, separados por vírgula.
O programa deve continuar solicitando os dados das frutas até que o usuário decida parar.
Quando o usuário decidir parar de cadastrar frutas, o programa deve exibir uma mensagem de encerramento e fechar o arquivo. */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    float preco;
} Fruta;

void menu(){
    printf("\nMenu de Cadastro de Frutas:\n");
    printf("1 - Cadastrar Fruta\n");
    printf("2 - Parar o Cadastro\n");
    printf("Escolha uma opcao: ");
}

int main(){
    Fruta f;
    FILE *file = fopen("./frutas.txt", "a");
    
    if (file == NULL){
        printf("Erro ao abrir o ficheiro\n");
        return 1;
    }

    int escolha = 0;
    while(escolha != 2){
        menu();
        
        if (scanf("%d", &escolha) != 1){
            while (getchar() != '\n');
            escolha = 0; 
        }

        if(escolha == 1){
            printf("Nome da fruta: ");
            scanf(" %[^\n]", f.nome);
            printf("Preco: ");
            scanf("%f", &f.preco);
            
            fprintf(file, "%s, %.2f\n", f.nome, f.preco);
            printf("%s cadastrada com sucesso.\n", f.nome);
            
        } else if(escolha == 2){
            printf("Encerrando o cadastro de frutas e fechando o ficheiro.\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
    fclose(file);
    return 0;
}