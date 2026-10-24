// Exercício 2 — Colisão entre bolas usando a matriz como ”mapa de calor”
// Atualmente a matriz (grade) serve apenas como fundo decorativo e não interage com as bolas.
// Tarefa: modifique o programa para que, toda vez que uma bola passar sobre uma célula da grade, o valor daquela célula na matriz mude de 0 para 1 (marcando a célula como ”visitada”), e a cor de desenho dessa célula passe a ser diferente (por exemplo, mais clara).
// Em seguida, adicione um contador (variável int normal, sem ser ponteiro) que mostra na tela quantas células já foram visitadas por pelo menos uma bola, atualizado a cada quadro.
// Dicas:
// • Você vai precisar converter a posição (x, y) em pixels da bola para índices de linha e coluna da matriz. Dica: coluna = (int)(b->pos.x / TAM CELULA).
// • Cuidado com os limites da matriz: verifique se a linha e a coluna calculadas estão dentro do intervalo [0, linhas) e [0, colunas) antes de acessar grade[linha][coluna], para não acessar memória fora dos limites alocados.
// • Para contar as células visitadas, você pode percorrer a matriz inteira a cada quadro (mais simples) ou manter um contador incremental que só aumenta quando uma célula passa de 0 para 1 pela primeira vez (mais eficiente).

#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define TAM_CELULA     40   // tamanho de cada célula da grade (matriz)


typedef struct {
    Vector2 pos;
    Vector2 vel;
    float   raio;
    Color   cor;
} Bola;

/* ---------------------------------------------------------------
 * cria uma MATRIZ dinâmica de inteiros (linhas x colunas)
 * Retorna um ponteiro para ponteiro (int **): cada posição do
 * vetor externo aponta para um vetor de inteiros (uma linha).
 * --------------------------------------------------------------- */
int **criarMatriz(int linhas, int colunas) {

    // aloca o vetor de ponteiros (um ponteiro por linha)
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    if (matriz == NULL) return NULL;

    for (int i = 0; i < linhas; i++) {
        // aloca cada linha como um vetor de inteiros
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            // Mudei para que todas recebam 0 (Não visitadas).
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

/* libera a memória da matriz: primeiro cada linha, depois o vetor de linhas */
void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);   // libera cada linha
    }
    free(matriz);           // libera o vetor de ponteiros
}

/* desenha a matriz na tela, célula por célula */
void desenharMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Color cor = (matriz[i][j] == 1) ? (Color){100, 180, 240, 255}  // Visitada (Clara)
                                             : (Color){15, 30, 55, 255};   // Não visitada (Escura)
            DrawRectangle(j * TAM_CELULA, i * TAM_CELULA,
                           TAM_CELULA - 2, TAM_CELULA - 2, cor);
        }
    }
}

/* ---------------------------------------------------------------
 * cria o vetor dinâmico de bolas
 * --------------------------------------------------------------- */
Bola *criarBolas(int quantidade) {
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));
    if (bolas == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        // usar (bolas + i) é o mesmo que &bolas[i]: aqui acessamos
        // o campo via ponteiro para deixar explícito o conceito.
        Bola *b = (bolas + i);
        b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50),
                             GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-4, 4),
                             (float)GetRandomValue(-4, 4) };
        b->raio = (float)GetRandomValue(10, 25);
        b->cor  = (Color){ GetRandomValue(100,255), GetRandomValue(100,255),
                            GetRandomValue(100,255), 255 };
    }
    return bolas;
}

/* atualiza a posição de UMA bola: recebe um PONTEIRO para a struct,
 * então as alterações afetam diretamente o vetor original (sem cópia) */
void atualizarBola(Bola *b) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    // rebate nas bordas
    if (b->pos.x - b->raio < 0 || b->pos.x + b->raio > LARGURA_JANELA)
        b->vel.x *= -1;
    if (b->pos.y - b->raio < 0 || b->pos.y + b->raio > ALTURA_JANELA)
        b->vel.y *= -1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA,
               "Ponteiros e Alocacao Dinamica - raylib");
    SetTargetFPS(60);

    int linhas   = ALTURA_JANELA / TAM_CELULA;
    int colunas  = LARGURA_JANELA / TAM_CELULA;
    int **grade  = criarMatriz(linhas, colunas);   // matriz dinâmica

    int quantidadeBolas = 12;
    Bola *bolas = criarBolas(quantidadeBolas);      // vetor dinâmico

    // Contador de células visitadas.
    int celulasVisitadas = 0;

    while (!WindowShouldClose()) {

        // percorre o vetor usando aritmética de ponteiros:
        // (bolas + i) aponta para o i-ésimo elemento do vetor
        for (int i = 0; i < quantidadeBolas; i++) {
            atualizarBola(bolas + i);

        // Converte a posição (x, y) em pixels da bola para linha e coluna da grade
            int col = (int)(bolas[i].pos.x / TAM_CELULA);
            int lin = (int)(bolas[i].pos.y / TAM_CELULA);

            // Verifica se está dentro dos limites da matriz antes de acessar
            if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                // Se a célula ainda não tiver sido visitada
                if (grade[lin][col] == 0) {
                    grade[lin][col] = 1;     // Marca como visitada
                    celulasVisitadas++;
                }
            }
        }

    // Exercício 1: 
    if(IsKeyPressed(KEY_SPACE)){

        quantidadeBolas += 1;
        Bola *bolas_adicionar = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));
        
        if (bolas_adicionar != NULL){
            bolas = bolas_adicionar;
            int novoIndice = quantidadeBolas - 1;
            bolas[novoIndice].pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50),
                                               (float)GetRandomValue(50, ALTURA_JANELA - 50) };
            bolas[novoIndice].vel = (Vector2){ (float)GetRandomValue(-4, 4),
                                               (float)GetRandomValue(-4, 4) };
            bolas[novoIndice].raio = (float)GetRandomValue(10, 25);
            bolas[novoIndice].cor  = (Color){ GetRandomValue(100, 255), GetRandomValue(100, 255),
                                              GetRandomValue(100, 255), 255 };
            }else{
            quantidadeBolas -= 1;
        }
    }

    if(IsKeyPressed(KEY_BACKSPACE)){
        if(quantidadeBolas > 0){
            quantidadeBolas -= 1;

            if (quantidadeBolas > 0){
            Bola *bolas_remover = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));
                if (bolas_remover != NULL){
                    bolas = bolas_remover;
                }
                }else{
                free(bolas);
                bolas = NULL;
            }
        }
    }
    // Aqui termina o Exercício 1.

        BeginDrawing();
            ClearBackground(RAYWHITE);

            desenharMatriz(grade, linhas, colunas);

            for (int i = 0; i < quantidadeBolas; i++) {
                DrawCircleV(bolas[i].pos, bolas[i].raio, bolas[i].cor);
            }

            // Exibe o contador de células visitadas
            DrawText(TextFormat("Celulas Visitadas: %d / %d", celulasVisitadas, linhas * colunas),
                     10, 30, 20, YELLOW);

            DrawText("Matriz (int**) e vetor de structs (Bola*) alocados com malloc",
                     10, 10, 18, WHITE);
            DrawText("Pressione ESC para sair", 10, ALTURA_JANELA - 25, 16, WHITE);

        EndDrawing();
    }

    // libera TODA a memória alocada dinamicamente antes de encerrar
    free(bolas);
    liberarMatriz(grade, linhas);

    CloseWindow();
    return 0;
}