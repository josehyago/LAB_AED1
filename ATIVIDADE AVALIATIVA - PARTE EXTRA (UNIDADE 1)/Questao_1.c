/* Exercício 1: Redimensionando o vetor dinâmico de structs
* Atualmente, o jogo possui um vetor contíguo de asteroides de tamanho fixo, alocado com malloc.
* Tarefa: Modifique o sistema para que o vetor cresça dinamicamente. Ao pressionar uma tecla, adicione um novo asteroide ao vetor.
* Dicas: 
* Utilize a função realloc para redimensionar o bloco de memória apontado pelo ponteiro do vetor original, em vez de recriar o vetor do zero. 
* Lembre-se de atualizar a variável que guarda a quantidade total de asteroides sempre que o vetor mudar de tamanho.   
* Inicialize os dados da nova struct usando a aritmética de ponteiros (ex: asteroides + i para acessar a nova posição equivalente a &asteroides[i]). 
*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

// Struct para a Nave do Jogador
typedef struct {
    Vector2 pos;
    float raio;
    int recursosColetados;
} Nave;

// Struct para o Asteroide
typedef struct {
    Vector2 pos;
    float raio;
    bool ativo;
} Asteroide;

// Protótipos das funções
Asteroide *criarAsteroides(int quantidade);
void desenharNave(Nave *n);
void desenharAsteroides(Asteroide *vetor, int quantidade);
void liberarAsteroides(Asteroide *vetor);

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "AED I - Navegacao Espacial");
    SetTargetFPS(60);

    // Inicializa a nave
    Nave nave = { (Vector2){ LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f }, 15.0f, 0 };

    // Inicializa vetor dinâmico de asteroides
    int qtdAsteroides = 5;
    Asteroide *asteroides = criarAsteroides(qtdAsteroides);

    
    while (!WindowShouldClose()) {
        // --- ATUALIZAÇÃO / MOVIMENTAÇÃO ---
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) nave.pos.x += 4.0f;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  nave.pos.x -= 4.0f;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    nave.pos.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  nave.pos.y += 4.0f;
        
        if (IsKeyPressed(KEY_SPACE)){
            qtdAsteroides += 1;
            Asteroide *vetor = (Asteroide *) realloc(asteroides, qtdAsteroides * sizeof(Asteroide));
            if(vetor != NULL){
                asteroides = vetor;
                int novoindice = qtdAsteroides - 1; 
                Asteroide *ast = (asteroides + novoindice);
            ast->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50), 
                                 (float)GetRandomValue(50, ALTURA_JANELA - 50) };
            ast->raio = (float)GetRandomValue(12, 25);
            ast->ativo = true;
            } else { qtdAsteroides -= 1;}
        }

        if (IsKeyPressed(KEY_BACKSPACE)){
            if (qtdAsteroides > 0){
            qtdAsteroides -= 1;
                if (qtdAsteroides > 0){
                Asteroide *vetor = (Asteroide *) realloc(asteroides, qtdAsteroides * sizeof(Asteroide));
                if (vetor != NULL){
                    asteroides = vetor;
                }else{
                    free(asteroides);
                    asteroides = NULL;}
            }
        }
        }
        // --- DESENHO ---
        BeginDrawing();
        ClearBackground(BLACK);

        // Desenha elementos
        desenharAsteroides(asteroides, qtdAsteroides);
        desenharNave(&nave);

        // Interface
        DrawText(TextFormat("Asteroides no Mapa: %d", qtdAsteroides), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Recursos Coletados: %d", nave.recursosColetados), 10, 35, 20, GREEN);

        EndDrawing();
    }

    // Liberação de memória
    liberarAsteroides(asteroides);
    CloseWindow();

    return 0;
}

// Cria e aloca dinamicamente o vetor contíguo de asteroides
Asteroide *criarAsteroides(int quantidade) {
    Asteroide *vetor = (Asteroide *) malloc(quantidade * sizeof(Asteroide));
    if (vetor == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Asteroide *ast = (vetor + i); // Aritmética de ponteiros
        ast->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50), 
                             (float)GetRandomValue(50, ALTURA_JANELA - 50) };
        ast->raio = (float)GetRandomValue(12, 25);
        ast->ativo = true;
    }
    return vetor;
}

void desenharNave(Nave *n) {
    DrawCircleV(n->pos, n->raio, BLUE);
}

void desenharAsteroides(Asteroide *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        Asteroide *ast = (vetor + i);
        if (ast->ativo) {
            DrawCircleV(ast->pos, ast->raio, GRAY);
        }
    }
}

void liberarAsteroides(Asteroide *vetor) {
    free(vetor);
}