// Você foi contratado para desenvolver um programa em C que permita armazenar nomes completos e idades de várias pessoas. O programa deve solicitar ao usuário o número de pessoas e, em seguida, permitir que ele digite o nome completo e a idade de cada pessoa.
// Seu programa deve alocar memória dinamicamente para armazenar os nomes em uma matriz de strings, e as idades devem ser armazenadas em um vetor. Após a entrada de todos os nomes e idades, o programa deve exibir os nomes armazenados.
// Aqui estão as especificações do programa:
// – O programa deve começar solicitando ao usuário o número de pessoas que deseja armazenar.
// – Em seguida, o programa deve pedir ao usuário que digite o nome completo de cada pessoa.
// – Os nomes devem ser armazenados em uma matriz alocada dinamicamente.
// – Após o nome, o programa deve solicitar a idade da pessoa.
// – As idades devem ser armazenadas em um vetor alocado dinamicamente.
// – Após a entrada de todos os nomes e idades, o programa deve exibir os nomes armazenados.
// – Certifique-se de tratar adequadamente a alocação dinâmica de memória e liberar a memória alocada corretamente após o uso.
// Observação: O programa deve ser capaz de armazenar até 100 nomes completos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, erro, i, x;
    do{
        erro = 0;
        printf("Digite a quantidade de pessoas (Max: 100): ");
        scanf("%d", &n);
        if(n > 100 || n < 1) erro = 1;
    }while(erro == 1);

    char **nomes = (char **) malloc(n * sizeof(char *)); 
    if (nomes == NULL) {
        printf("Erro ao alocar memoria para os nomes.\n");
        exit (1);
    }

     for (i = 0; i < n; i++) {
        nomes[i] = (char *) malloc(100 * sizeof(char));
        if (nomes[i] == NULL) {
            printf("Erro ao alocar memoria para as colunas dos nomes.\n");
            for (x = 0; x < i; x++) free(nomes[x]);
            free(nomes);
            exit (1);
        }
    }

      int *idades = (int *) malloc(n * sizeof(int));
    if (idades == NULL) {
        printf("Erro ao alocar memoria para as idades.\n");
        for (i = 0; i < n; i++) free(nomes[i]);
        free(nomes);
        exit (1);
    }

    getchar();

    for (i = 0; i < n; i++) {
        printf("\nPessoa: %d\n", i + 1);
        
        printf("Digite o nome completo: ");
        fgets(nomes[i], 100, stdin);
        nomes[i][strcspn(nomes[i], "\n")] = '\0';

        printf("Digite a idade: ");
        scanf("%d", &idades[i]);
        
        getchar(); 
    }

    printf("\nCadastros: \n");
    for (i = 0; i < n; i++) {
        printf("Pessoa %d: nome: %s\n", i + 1, nomes[i]);
    }

    for (i = 0; i < n; i++) {
        free(nomes[i]);
    }
    free(nomes);
    free(idades);

    return 0;
}