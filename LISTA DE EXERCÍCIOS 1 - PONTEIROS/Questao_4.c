// Crie um programa para calcular a área e o perímetro de um hexágono. O seu programa deve implementar uma função chamada calcula_hexagono que calcula a área e o perímetro de um hexágono regular de lado l. A função deve obedecer ao seguinte protótipo: void calcula_hexagono(float l, float *area, float *perimetro); A área e o perímetro de um hexágono regular são dados, respectivamente, por:
// Obs: Para os cálculos, utilize as funções sqrt e pow do módulo math da biblioteca padrão de C. Em seguida, crie a função principal do programa e utilize a função calcula_hexagono para calcular a área e o perímetro de um hexágono de lado l informado pelo usuário.

#include <stdio.h>
#include <math.h>

void calcula_hexagono(float l, float *area, float *perimetro){
    *area = (3 * pow(l, 2) * sqrt(3)) / 2;
    *perimetro = 6 * l;
}

int main(){
    float l, area, perimetro;
    float *parea, *pperimetro;

    parea = &area;
    pperimetro = &perimetro;

    printf("Informe o valor de l: ");
    scanf("%f", &l);
    calcula_hexagono(l, parea, pperimetro);

    printf("Area do hexagono: %.2f\n", area);
    printf("Perimetro do hexagono: %.2f\n", perimetro);

    return 0;
}
