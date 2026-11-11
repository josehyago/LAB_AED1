/* 
* Lista Encadeadas (Simples)
* Listas Duplas Encadeadas
* Listas Circulares
-------------
* Pilhas
* Pilhas com Listas
* Filas
* Filas com Listas
-------------
* Algoritmos
* int vet[N];
-------------
* Alocação Dinâmica
* int *vet = (int *) malloc(N * sizeof(int));
* vet = realloc (int, 2 * N * sizeof(int));
-------------
* | 1 | 5 | 0 |
*   0   1   2
-------------
* | 1 | -> | 5 | -> | 0 |
* Cada um é um nó
-------------
* typedef struct no{
* int valor; // Valor que o Nó armazenamento
* No *prox; // Endereço do próx elemento
* } No;
-------------
* int num - 0;
* No *lista = NULL;
* No *novo = (No*) malloc(sizeof(No));
* novo->valor = num;
* novo->prox = lista; 
*/