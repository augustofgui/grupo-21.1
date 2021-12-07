#ifndef FITAS_H
#define FITAS_H

#include "geral.h"

// ----- Defines de controle de tamanho e ordem das fitas
#define TEXT 50                 // Tamanho máximo da string de texto
#define TAM_BLOCO 20            // Tamanho inicial de cada bloco
#define NUM_FITAS_ENTRADA 20    // Número de fitas de entrada
#define NUM_FITAS_SAIDA 20      // Número de fitas de saída
#define NUM_FITAS NUM_FITAS_ENTRADA + NUM_FITAS_SAIDA // Número total de fitas

// ----- Definindo as estruturas das fitas
// ----- as separando em Fita (Unitária) e
// ----- Fitas (conjunto).

typedef struct {
    FILE * arquivo;         // Ponteiro para arquivo.
    int quant_itens;        // Quantidades total de itens.
    int tam_ultimo_bloco;   // O tamanho do ultimo bloco inserido.
    bool preenchida;        // Booleano que diz se a fita tem algo escrito nela.
} Fita;

typedef struct {
    Fita entrada[NUM_FITAS_ENTRADA]; // Fitas de entrada.
    Fita saida[NUM_FITAS_SAIDA]; // Fitas de saida.
} Fitas;

// ----- Funções que agem das fitas.
Fitas cria_fitas();
Fita nova_fita(char * caminho, int quant_itens, int tam_ultimo_bloco, bool preenchida);
void remove_fitas(Fitas *fitas);
void fitas_rewind(Fitas * fitas);
void cria_fitas_tipo(Fita * vetor, int n, char * tipo);
void escreve_na_fita(FILE * arquivo_binario, Fita * fita_destino, int tam, Estatistica * estatistica, bool imprimir_dados);
void string_caminho_fitas(char *tipo, char * num, char * str_out);
void string_arquivo_fitas(char *tipo, char * num, char * str_out);

#endif // FITA_H