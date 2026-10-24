// Exercício 1 — Novo tipo de item: escudo
// Atualmente a union DadosItem só conhece dados de arma e de poção.
// Tarefa: adicione um terceiro tipo de item, ITEM_ESCUDO, que aumenta uma nova propriedade armadura do jogador.
// Dicas:
// • Crie uma struct DadosEscudo com um campo int absorcao.
// • Adicione esse tipo como um novo campo da union DadosItem.
// • Acrescente ITEM_ESCUDO ao enum TipoItem e trate o novo caso em criarItens, aplicarItem e desenharItem.
//• Lembre-se de adicionar o campo int armadura à struct Jogador

#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define RAIO_JOGADOR   20.0f
#define TOTAL_ITENS    10

typedef enum {
    ITEM_ARMA,
    ITEM_POCAO,
    ITEM_ESCUDO // Adicionando escudo no enum.
} TipoItem;

typedef struct {
    float dano;
    int   alcance;
} DadosArma;

typedef struct {
    int cura;
} DadosPocao;

// Struct do escudo.
typedef struct {
    int absorcao;
} DadosEscudo;

/* union: em cada Item só um destes dois campos é válido por vez,
 * e isso é decidido pelo campo "tipo" (enum) da struct Item */
typedef union {
    DadosArma  arma;
    DadosPocao pocao;
    DadosEscudo escudo; // Adicionando escudo na union.
} DadosItem;

typedef struct {
    Vector2   pos;
    float     raio;
    TipoItem  tipo;
    DadosItem dados;
    bool      coletado;
} Item;

typedef struct {
    Vector2 pos;
    float   raio;
    int     vida;
    float   dano;
    int armadura; // Int pro escudo.
} Jogador;

/* cria o vetor dinâmico de itens sorteando tipo e preenchendo a
 * union de acordo com o tipo sorteado */
Item *criarItens(int quantidade) {
    Item *itens = (Item *)malloc(quantidade * sizeof(Item));
    if (itens == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Item *it = (itens + i);
        it->pos      = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30),
                                   GetRandomValue(30, ALTURA_JANELA - 30) };
        it->raio     = 12.0f;
        it->coletado = false;
        it->tipo     = (TipoItem)GetRandomValue(ITEM_ARMA, ITEM_ESCUDO);

        if (it->tipo == ITEM_ARMA) {
            it->dados.arma.dano    = (float)GetRandomValue(2, 8);
            it->dados.arma.alcance = GetRandomValue(1, 3);
        } else if (it->tipo == ITEM_POCAO) {
            it->dados.pocao.cura = GetRandomValue(10, 30);
        } else {
            it->dados.escudo.absorcao = GetRandomValue(5, 15); // Valores pro escudo.
        }
    }
    return itens;
}

/* recebe PONTEIROS para o jogador e para o item: aplica o efeito do
 * item lendo o campo correto da union de acordo com o enum "tipo" */
void aplicarItem(Jogador *j, Item *item) {
    switch (item->tipo) {
        case ITEM_ARMA:
            j->dano += item->dados.arma.dano;
            break;
        case ITEM_POCAO:
            j->vida += item->dados.pocao.cura;
            break;
            case ITEM_ESCUDO:
            j->armadura += item->dados.escudo.absorcao; // Novo item: escudo.
            break;
    }
    item->coletado = true;
}

bool colidiu(Vector2 a, float raioA, Vector2 b, float raioB) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float distancia2 = dx * dx + dy * dy;
    float somaRaios2 = (raioA + raioB) * (raioA + raioB);
    return distancia2 <= somaRaios2;
}

void desenharItem(Item *item) {
    if (item->coletado) return;

    Color cor;
    switch (item->tipo){
        case ITEM_ARMA:
        cor = RED;
        break;
        case ITEM_POCAO:
        cor = GREEN;
        break;
        case ITEM_ESCUDO:
        cor = GRAY; // Cor pro escudo.
        break;
}
    DrawCircleV(item->pos, item->raio, cor);
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 3 - Union + Enum + Struct");
    SetTargetFPS(60);
    // Novo campo pro escudo.
    Jogador jogador = { { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f }, RAIO_JOGADOR, 100, 5.0f, 0 };
    Item *itens = criarItens(TOTAL_ITENS); // vetor dinâmico de struct com union

    while (!WindowShouldClose()) {

        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador.pos.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador.pos.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador.pos.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador.pos.y += vel;

        for (int i = 0; i < TOTAL_ITENS; i++) {
            Item *it = (itens + i);
            if (!it->coletado && colidiu(jogador.pos, jogador.raio, it->pos, it->raio)) {
                aplicarItem(&jogador, it); // &jogador: ponteiro para struct
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < TOTAL_ITENS; i++) {
                desenharItem(itens + i);
            }

            DrawCircleV(jogador.pos, jogador.raio, BLUE);

            DrawText(TextFormat("Vida: %d   Dano: %.1f | Armadura: %d", jogador.vida, jogador.dano, jogador.armadura), 10, 10, 22, DARKGRAY);
            DrawText("Vermelho = arma (aumenta dano) | Verde = pocao (cura) | Cinza = escudo (armadura)", 10, 34, 18, GRAY);
            DrawText("Setas movem o jogador | ESC sai", 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    free(itens); // libera o vetor dinâmico

    CloseWindow();
    return 0;
}