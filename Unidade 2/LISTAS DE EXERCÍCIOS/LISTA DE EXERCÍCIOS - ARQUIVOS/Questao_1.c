/*Faça um programa em C que solicita ao usuário informações de funcionários via teclado. 
As informações digitadas pelo o usuário são: id, nome e salário do funcionário. 
Armazene as informações digitadas pelo usuário em um arquivo texto.
*/

#include <stdio.h>

int main(){
    int id;
    char nome[20];
    float salario;

    printf("Digite as informacoes do funcionario (Id, Nome, Salario): ");
    scanf("%d %s %f", &id, nome, &salario);

    FILE *file = fopen("./informacoes.txt", "w");
    
    fprintf(file, "ID: %d | Nome: %s | Salario: %.2f", id, nome, salario);

    fclose(file);
    return 0;
}