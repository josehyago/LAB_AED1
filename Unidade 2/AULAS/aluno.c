#include <stdio.h>
#include "aluno.h"
#include <string.h>

struct aluno{
    char nome[20];
    float nota;
};

Aluno criarAluno(char nome[], float nota){
    Aluno a;
    strcpy(a.nome, nome);
    a.nota = nota;
    return a;
}

void mostrarAluno(Aluno a){
    printf("%s - Nota: %.1f\n", a.nome, a.nota);
}