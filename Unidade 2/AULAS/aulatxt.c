#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arquivo;
    int c;
    char linha[100];
    // arquivo = fopen("entrada.txt", "w");
    arquivo = fopen("entrada.txt", "r");
    if(arquivo == NULL){
        printf("Nao foi possivel criar o arquivo");
        exit(1);
    }
    else{
        printf("Arquivo criado");
    }
    // fputc('A', arquivo); // Escreve no arquivo
    // fputs(" Hello World!", arquivo); // Escreve no arquivo
    // fprintf(arquivo, "\nTeste com fprintf"); // Escreve no arquivo
    // c = fgetc(arquivo); // Ler um caractere por vez
    // printf(" %c", c);
    // fgets(linha, 100, arquivo); // Ler uma linha por vez do arquivo
    // fscanf(arquivo, "%s", linha);
    // printf("%s", linha);
    while(!feof(arquivo)){ // Enquanto não chegar ao final do arquivo
        c = fgetc(arquivo);
        printf("%c", c);
    }
    fclose(arquivo);
    return 0;
}