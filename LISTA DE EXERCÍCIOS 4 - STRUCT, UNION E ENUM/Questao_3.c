// Escreva um programa que implementa uma struct Data com os campos dia, mês e ano. O mês deve ser armazenado como um enum com os valores JANEIRO, FEVEREIRO, MARÇO, ABRIL, MAIO, JUNHO, JULHO, AGOSTO, SETEMBRO, OUTUBRO, NOVEMBRO e DEZEMBRO. O programa deve ler a data e imprimir a data no formato dd/mm/aaaa.
#include <stdio.h>

typedef enum{
    JANEIRO = 1,
    FEVEREIRO,
    MARCO,
    ABRIL,
    MAIO,
    JUNHO,
    JULHO,
    AGOSTO,
    SETEMBRO,
    OUTUBRO,
    NOVEMBRO,
    DEZEMBRO
} Mes;

typedef struct{
    int dia;
    int ano;
    Mes mes;
} Data;

int main() {
    Data data;
    int mes_int;

    printf("Digite o dia: ");
    scanf("%d", &data.dia);

    printf("Digite o numero do mes (1 a 12): ");
    scanf("%d", &mes_int);

    data.mes = (Mes)mes_int; 

    printf("Digite o ano: ");
    scanf("%d", &data.ano);

    printf("Data formatada: %02d/%02d/%04d\n", data.dia, data.mes, data.ano);

    return 0;
}