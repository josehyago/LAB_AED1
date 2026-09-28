/*Faça um programa em C que solicita ao usuário informações de funcionários via teclado. 
As informações digitadas pelo o usuário são: id, nome e salário do funcionário. 
Armazene as informações digitadas pelo usuário em um arquivo texto.
*/

#include <stdio.h>

int main(){
    int id;
    char nome[50];
    float salario;

    printf("Digite as informacoes do funcionario: \n");

    printf("ID: ");
    scanf("%d", &id);

    printf("Nome completo: ");
    scanf(" %[^\n]", nome);

    printf("Salario: ");
    scanf("%f", &salario);

    FILE *file = fopen("./informacoes.txt", "w");

    if (file == NULL){
        printf("Erro ao criar o ficheiro\n");
        return 1;
    }
    
    fprintf(file, "ID: %d | Nome: %s | Salario: %.2f\n", id, nome, salario);

    fclose(file);
    printf("Dados guardados com sucesso.\n");
    return 0;
}