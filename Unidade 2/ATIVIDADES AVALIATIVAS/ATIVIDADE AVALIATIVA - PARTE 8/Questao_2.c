/*
 Exercício 2 — Reaproveitando o módulo em outro programa
 Atualmente o módulo entidade só é usado por atividade8.c.
 Tarefa: crie um novo arquivo atividade8b.c com um main bem simples (por exemplo, criar 3 entidades de tipos diferentes e apenas desenhá-las na tela, sem jogabilidade) que reutiliza entidade.h/entidade.c sem copiar nenhuma linha de código do módulo.
 Dicas:
 • Compile com gcc atividade8b.c entidade.c -o atividade8b ... (os mesmos flags de sempre).
 • Isso demonstra o principal benefício de um módulo: o mesmo código é reaproveitado por dois programas diferentes.
*/

/*
 gcc Questao_2.c entidade.c -o Questao_2 -lraylib -lopengl32 -lgdi32 -lwinmm
 ./Questao_2.exe
*/

#include "raylib.h"
#include "entidade.h"
#include <stdlib.h>
#include <time.h>

int main(void){
    InitWindow(800, 600, "Atividade 8b");
    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){ 400, 300 });
    Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){ 200, 200 });
    Entidade *item = entidadeCriar(ENTIDADE_ITEM, (Vector2){ 600, 400 });

    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            entidadeDesenhar(jogador);
            entidadeDesenhar(inimigo);
            entidadeDesenhar(item);
            
        EndDrawing();
    }

    free(jogador);
    free(inimigo);
    free(item);

    CloseWindow();
    return 0;
}