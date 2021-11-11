#include <stdio.h>
#include <stdlib.h>

typedef int TipoApontador;

typedef struct registro {
    long int inscricao;
    float nota;
    char estado[2];
    char cidade[50];
    char curso [30];
} Registro;