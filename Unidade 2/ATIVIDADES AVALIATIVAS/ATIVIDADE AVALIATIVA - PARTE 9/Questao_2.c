/* 
 Exercício 2 — Contando entidades por tipo
 Atualmente não há como saber, de fora do TAD, quantas entidades de um determinado tipo existem sem percorrer manualmente todo o inventário.
 Tarefa: implemente int inventarioContarPorTipo(Inventario *inv, TipoEntidade tipo), que devolve quantas entidades do tipo informado estão armazenadas.
 Dicas:
 • Implemente a função dentro de inventario.c, percorrendo inv->vetor internamente (isso só é possível ali, pois é o único arquivo que conhece a struct).
 • Declare o protótipo em inventario.h para que atividade9.c possa chamá-la.
 • Use essa função para exibir, na tela, quantos itens (ENTIDADE_ITEM) ainda restam no mapa.
*/

/* 
 gcc Questao_2.c entidade.c inventario.c -o Questao_2 -lraylib -lopengl32 -lgdi32 -lwinmm
 ./Questao_2.exe
*/

#include "raylib.h"
#include "entidade.h"
#include "inventario.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA  800
#define ALTURA_JANELA   600
#define MAX_ENTIDADES   12 // Alterado temporariamente para testar o inventário cheio
#define TOTAL_INIMIGOS  5
#define TOTAL_ITENS     6
#define DANO_TIRO       20

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 9 - TAD (Tipo Abstrato de Dados)");
    SetTargetFPS(60);

    Inventario *inventario = inventarioCriar(MAX_ENTIDADES);

    // índice 0 do inventário é sempre o jogador
    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR,
                                      (Vector2){ LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f });
    inventarioAdicionar(inventario, jogador);

    for (int i = 0; i < TOTAL_INIMIGOS; i++) {
        Vector2 pos = { GetRandomValue(30, LARGURA_JANELA - 30), GetRandomValue(30, ALTURA_JANELA - 30) };
        inventarioAdicionar(inventario, entidadeCriar(ENTIDADE_INIMIGO, pos));
    }
    for (int i = 0; i < TOTAL_ITENS; i++) {
        Vector2 pos = { GetRandomValue(30, LARGURA_JANELA - 30), GetRandomValue(30, ALTURA_JANELA - 30) };
        inventarioAdicionar(inventario, entidadeCriar(ENTIDADE_ITEM, pos));
    }

    int pontuacao = 0;

    while (!WindowShouldClose()) {

        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador->pos.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador->pos.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador->pos.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador->pos.y += vel;

        // percorre o inventário só através da sua interface pública
        for (int i = 1; i < inventarioTotal(inventario); i++) {
            Entidade *e = inventarioObter(inventario, i);
            if (!entidadeColidiu(jogador, e)) continue;

            if (e->tipo == ENTIDADE_ITEM) {
                pontuacao += e->extra.valor;
                inventarioRemover(inventario, i);
                i--;
            } else if (e->tipo == ENTIDADE_INIMIGO) {
                entidadeAplicarDano(jogador, e->extra.dano);
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 1; i < inventarioTotal(inventario); i++) {
                Entidade *e = inventarioObter(inventario, i);
                if (e->tipo != ENTIDADE_INIMIGO) continue;
                if (!entidadeColidiu(jogador, e)) {
                    entidadeAplicarDano(e, DANO_TIRO);
                    if (e->vida <= 0) inventarioRemover(inventario, i);
                    break;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < inventarioTotal(inventario); i++) {
                entidadeDesenhar(inventarioObter(inventario, i));
            }
            // Exercício 1:
            if (inventarioEstaCheio(inventario)){
                DrawText("AVISO: Inventario Cheio!", 10, 58, 18, RED);
            }
            // Exercício 2:
            int itensRestantes = inventarioContarPorTipo(inventario, ENTIDADE_ITEM);
            DrawText(TextFormat("Itens restantes no mapa: %d", itensRestantes), 10, 72, 18, DARKGREEN);

            DrawText(TextFormat("Vida: %d   Pontuacao: %d", jogador->vida, pontuacao), 10, 10, 22, DARKGRAY);
            DrawText(TextFormat("Entidades no inventario: %d", inventarioTotal(inventario)), 10, 34, 18, GRAY);
            DrawText("Setas movem | ESPACO atira | ESC sai", 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    inventarioDestruir(inventario); // uma única chamada libera tudo (entidades + vetor interno + struct)

    CloseWindow();
    return 0;
}