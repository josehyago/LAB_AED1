/* Questão 1) Escreva um programa em C que manipula dados dos alunos da disciplina de Algoritmos e Estruturas de Dados I da UFERSA Pau dos Ferros. Seu programa deverá utilizar os tipos estruturados e o vetor definidos a seguir:

struct aluno {
 int mat;
 char nome[81];
 float notas[3];
 float media;
};
typedef struct aluno Aluno;
struct turma {
 char id; // caractere que identifica a turma, por exemplo, A ou B
 int vagas; // números de vagas disponíveis para fechar a turma
 Aluno* alunos[MAX_VAGAS];
};
typedef struct turma Turma;
Turma* turmas[MAX_TURMAS];


Deve-se levar em consideração que é ofertado um número máximo de turmas (definido pela constante simbólica MAX_TURMAS) e um número máximo de vagas para cada turma (definido pela constante simbólica MAX_VAGAS). Sabendo dessas informações, faça o que se pede nos itens a seguir:
 a) Implemente uma função que cria uma turma, fornecendo-lhe um identificador. Essa função deve ser responsável por indicar que a turma não tem alunos matriculados, atribuindo a constante NULL a cada um dos elementos do vetor de ponteiros.
 Protótipo: Turma* cria_turma(char id);
 b) Implemente uma função que recebe os dados de um aluno e o matricula em uma das turmas, caso haja vaga disponível. Inicialize suas notas com zero.
 Protótipo: void matricula_aluno(Turma* turma, int mat, char* nome);
 c) Implemente uma função que lança as notas e calcula a média dos alunos de uma determinada turma.
 Protótipo: void lanca_notas(Turma* turma);
 d) Implemente uma função que imprime os dados de todos os alunos de uma turma.
 Protótipo: void imprime_alunos(Turma* turma);
 e) Implemente uma função que imprime os dados de todas as turmas.
 Protótipo: void imprime_turmas(Turma** turmas, int n);
 f) Implemente uma função para procurar uma turma.
 Protótipo: Turma* procura_turma(Turma** turmas, int n, char id);
OBS.: Forneça um menu de interação com o usuário, tomando como base o exemplo de execução a seguir (o texto em negrito representa a entrada do usuário):
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_VAGAS 3
#define MAX_TURMAS 5

struct aluno {
 int mat;
 char nome[81];
 float notas[3];
 float media;
};
typedef struct aluno Aluno;
struct turma {
 char id; /* caractere que identifica a turma, por exemplo, A ou B */
 int vagas; /* números de vagas disponíveis para fechar a turma */
 Aluno* alunos[MAX_VAGAS];
};
typedef struct turma Turma;
Turma* turmas[MAX_TURMAS] = {NULL};

Turma* cria_turma(char id);
void imprime_turmas(Turma** turmas, int n);
void matricula_aluno(Turma* turma, int mat, char* nome);
void lanca_notas(Turma* turma);
void imprime_alunos(Turma* turma);
Turma* procura_turma(Turma** turmas, int n, char id);
void libera_memoria(Turma** turmas, int n);

int main(){
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_NUMERIC, "C");
    int opcao, mat;
    char id, nome[81];


    printf("Bem-vindo ao Programa de Gerenciamento de Turmas!\n");
    printf("Este programa gerencia as turmas ofertadas, fornecendo as funcionalidades de matricula, lancamento de notas e listagem de alunos.\n");
    printf("Autor: Ada Lovelace      Versao: 1.0\n");
    do{
    printf("\nMENU:\n1 - Criar turma\n2 - Listar turmas\n3 - Matricular aluno\n4 - Lancar notas\n5 - Listar alunos\n6 - Sair\n");
    printf("\nDigite sua opcao: ");
    scanf("%d", &opcao);
    getchar();
    switch (opcao){
    case 1:
        printf("\nCriando turma...\n");
        printf("Digite um id: ");
        scanf(" %c", &id);
        cria_turma(id);
        break;

    case 2: 
        printf("\nListando turmas...\n");
        imprime_turmas(turmas, MAX_TURMAS);
        break;

    case 3:
        printf("\nMatriculando aluno...\n");
        
        printf("Digite o id da turma: ");
        scanf(" %c", &id);
        
        Turma* turma_encontrada = procura_turma(turmas, MAX_TURMAS, id);

        if (turma_encontrada == NULL){
            printf("Turma inexistente!\n");
            break;
        }

        printf("Digite a matricula: ");
        scanf("%d", &mat);
        getchar();
        
        printf("Digite o nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';
        matricula_aluno(turma_encontrada, mat, nome);

        break;
    case 4:
        printf("\nLancando notas...\n");
        printf("Digite o id da turma: ");
        scanf(" %c", &id);
        turma_encontrada = procura_turma(turmas, MAX_TURMAS, id);
        if (turma_encontrada == NULL){
            printf("Turma inexistente!\n");
            break;
        }
        lanca_notas(turma_encontrada);

        break;
    case 5:
        printf("\nListando alunos...\n");
        printf("Digite o id da turma: ");
        scanf(" %c", &id);
        turma_encontrada = procura_turma(turmas, MAX_TURMAS, id);
        if (turma_encontrada == NULL){
            printf("Turma inexistente!\n");
            break;
        }
        imprime_alunos(turma_encontrada);
        break;
    case 6:
        printf("\nObrigado por usar este programa!\n");
        break;
    default:
        printf("\nOpcao invalida!\n");
        break;
    }
}while(opcao != 6);
    
    libera_memoria(turmas, MAX_TURMAS);
    return 0;
}

Turma* cria_turma(char id){
    
    for(int i = 0; i < MAX_TURMAS; i++){
        if(turmas[i] != NULL && id == turmas[i]->id){
            printf("\nTurma já existente.\n");
            return NULL;
        }
    }

       for(int i = 0; i < MAX_TURMAS; i++){
        if(turmas[i] == NULL){

            turmas[i] = (Turma*) malloc(sizeof(Turma));
            if(turmas[i] == NULL){
                printf("\nErro de falta de memória!\n");
                exit(1);
            }

            turmas[i]->id = id;
            turmas[i]->vagas = MAX_VAGAS;

            for(int j = 0; j < MAX_VAGAS; j++) {
                turmas[i]->alunos[j] = NULL;
            }

            printf("Turma %c criada com sucesso!\n", id);
            return turmas[i];
        }
    }

    printf("\nErro: Limite máximo de turmas atingido!\n");
    return NULL;
}

void imprime_turmas(Turma** turmas, int n){
    int encontradas = 0;
    for (int i = 0; i < n; i++){
        if (turmas[i] != NULL){
            printf("Turma %c %d vagas disponiveis\n", turmas[i]->id, turmas[i]->vagas);
            encontradas++;
        }
    }
    if (encontradas == 0){
        printf("Nenhuma turma cadastrada!\n");
    }
}

void matricula_aluno(Turma* turma, int mat, char* nome){
    if(turma == NULL || turma->vagas == 0){
        printf("Não há vagas disponíveis nesta turma!\n");
        return;
    }

    Aluno* novo_aluno = (Aluno*) malloc(sizeof(Aluno));
    if (novo_aluno == NULL){
        printf("Erro na alocação de memória para o aluno!\n");
        exit (1);
    }

    novo_aluno->mat = mat;
    strcpy(novo_aluno->nome, nome);
    
    for (int i = 0; i < 3; i++){
        novo_aluno->notas[i] = 0.0f;
    }
    novo_aluno->media = 0.0f;

    for (int i = 0; i < MAX_VAGAS; i++){
        if (turma->alunos[i] == NULL) {
            turma->alunos[i] = novo_aluno;
            turma->vagas--; 
            printf("Aluno matriculado com sucesso!\n");
            return;
        }
    }
}

void lanca_notas(Turma* turma){

    for(int i = 0; i < MAX_VAGAS; i++){
    if (turma->alunos[i] != NULL){
        float soma = 0.0f;

        printf("Matricula: %d     ", turma->alunos[i]->mat);
        printf("Aluno: %s\n", turma->alunos[i]->nome);

        for (int j = 0; j < 3; j++){
            printf("Digite a nota %d: ", j + 1);
            scanf("%f", &turma->alunos[i]->notas[j]);
            getchar();
            soma += turma->alunos[i]->notas[j];
        }

        turma->alunos[i]->media = soma / 3.0f;
        }
    }
}

void imprime_alunos(Turma* turma){
    for (int i = 0; i < MAX_VAGAS; i++){
        if (turma->alunos[i] != NULL){
            printf("Matricula: %d\n", turma->alunos[i]->mat);
            printf("Nome: %s\n", turma->alunos[i]->nome);
            printf("Media: %.1f\n", turma->alunos[i]->media);
        }
    }
}

Turma* procura_turma(Turma** turmas, int n, char id) {
    for (int i = 0; i < n; i++) {
        if (turmas[i] != NULL && turmas[i]->id == id){
            return turmas[i];
        }
    }
    return NULL;
}

void libera_memoria(Turma** turmas, int n){
    for (int i = 0; i < n; i++){
        if (turmas[i] != NULL){
            for (int j = 0; j < MAX_VAGAS; j++){
                if (turmas[i]->alunos[j] != NULL){
                    free(turmas[i]->alunos[j]);
                }
            }
            free(turmas[i]);
        }
    }
}