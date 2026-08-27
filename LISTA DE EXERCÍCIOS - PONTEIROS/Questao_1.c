//Quais serão os valores de x, y e p ao final do trecho de código abaixo:

#include <stdio.h>
int main(){
    int x, y, *p;
    y = 0;
    p = &y;
    x = *p;
    x = 4;
    (*p)++;
    --x;
    (*p) += x;

    return 0;
}

// Resposta: X = 3, Y = 4, P = &y