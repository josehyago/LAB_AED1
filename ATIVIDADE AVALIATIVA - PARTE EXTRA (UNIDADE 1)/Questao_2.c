/* Exercício 2: Diferenciando recursos com enumerações (enum)Atualmente todos os asteroides são iguais.
* Tarefa: Crie um tipo enum chamado TipoAsteroide para representar diferentes categorias (ex: ASTEROIDE_GELO, ASTEROIDE_METAL, ASTEROIDE_RADIOATIVO) 
* e adicione-o como campo dentro da struct do asteroide.
* Dicas: 
* O enum não guarda nenhum dado extra, apenas nomeia constantes inteiras, tornando o código mais legível do que usar números mágicos.   
* Crie uma função que receba um TipoAsteroide e use um switch para decidir a cor do asteroide ao desenhá-lo na tela.  
*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef enum{
    ASTEROIDE_GELO,
    ASTEROIDE_METAL,
    ASTEROIDE_RADIOATIVO
} TipoAsteroide;    

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
    TipoAsteroide ta;
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
            ast->ta = (TipoAsteroide)GetRandomValue(ASTEROIDE_GELO, ASTEROIDE_RADIOATIVO);
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
        ast->ta = (TipoAsteroide)GetRandomValue(ASTEROIDE_GELO, ASTEROIDE_RADIOATIVO);
    }
    return vetor;
}

void desenharNave(Nave *n) {
    DrawCircleV(n->pos, n->raio, BLUE);
}

void desenharAsteroides(Asteroide *vetor, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        Color cor;
        Asteroide *ast = (vetor + i);
        if (ast->ativo) {
            switch(ast->ta){
                case ASTEROIDE_GELO: cor = SKYBLUE;
                break;
                case ASTEROIDE_METAL: cor = DARKGRAY;
                break;
                case ASTEROIDE_RADIOATIVO: cor = LIME;
                break;
            }
            DrawCircleV(ast->pos, ast->raio, cor);
        }
    }
}

void liberarAsteroides(Asteroide *vetor) {
    free(vetor);
}