#ifndef geral_h
#define geral_h

/* ED2 - TP 1 -> https://github.com/augustofgui/ed2-tp1
    - Augusto Guilarducci (20.1.4012)
    - Caio Monteiro (20.1.4110)
    - Paulo Correa (20.1.4036)
    - Pedro Lucas Damasceno (20.1.4003)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct registro
{
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[5000];
} Registro;

//Métodos de pesquisa
int sequencial_Indexado(FILE *arquivo_Binario, int n_Metodo, int n_Registros, int n_Situacao, int n_Chave, char argv[5]);
//Funções dos métodos de pesquisa
int SI_buscar_Indice(int *tabela_Indice, int tam_Tabela, int n_Situacao, int n_Chave);
void SI_montar_Tabela(FILE *arquivo_Binario, int *tabela_Indice, int itens_Pagina);
int SI_defineItensPagina(int n_Registros);
//Verificação dos parâmetros de execução
void verif_Parametros(int argc, char *argv[]);
//Criação do arquivo binário a partir dos parâmetros
FILE *criar_Arquivo(int n_Metodo, int n_Registros, int n_Situacao);
//Imprimir resultado
void imprimir_Registro(Registro x);
void imprimir_NaoEncontrado(int n_Chave);

#endif