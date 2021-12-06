#include "../headers/geral.h"
#include "../headers/intercalacao_substituicao_selecao.h"
#include "../headers/heap_min.h"

#define TAM 10 // heap
#define NUM_BLOCK 20 // numero de blocos

int N = TAM;

void preencheVetor(Registro* vetor, FILE* fileEntrada) {
    for(int i = 1; i <= TAM; i++) {
        fread(&vetor[i], sizeof(*vetor), 1, fileEntrada);
    }
    Constroi(vetor, &N);
    Imprime(vetor, &N);
}

void converter_para_char (int num, char* c) {
    snprintf(c, sizeof(c), "%d", num);
}

void esvaziarVetor (Registro* vetor, int* n) {
    char block[50], bin[5], num[33];
    Registro Min;
    strcpy(block, "Bloco");
    strcpy(bin, ".bin");
    FILE* fileSaida;

    int tamanho = *n;
    for(int i = 0; i < tamanho; i++) {  
        Min = RetiraMin(vetor, n);
        Imprime(vetor, n);
        convertToChar(Min.nota, num);
        strcat(block, num);
        strcat(block, bin);
        fileSaida = fopen(block, "ab");
        strcpy(block, "Bloco");
        fwrite(&Min, sizeof(Min), 1, fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }
}

void sub (FILE* nome_arquivo, Registro* vetor, int numeroArq, int* n ) {
    int fita = 1;
    Registro Mini;
    Registro Item;
    Item.f = fita;

    char block[50];
    char txt[5];
    char num[33];
    
    strcpy(block, "Bloco");
    strcpy(txt, ".bin");

    preencheVetor(vetor, nome_arquivo);

    FILE* fileSaida = fopen("Bloco1.bin", "ab");
    Mini = RetiraMin(vetor, n);
    fwrite(&Mini, sizeof(Mini), 1, fileSaida);
    fclose(fileSaida);

    while (fread(&Item, sizeof(Item), 1, nome_arquivo) == 1) {
        if(Item.nota < Mini.nota) {
            if(fita == NUM_BLOCK) {
                fita = 1;
            }
            Item.f = fita + 1;
            Insere(&Item,vetor,n);
         }
        if(Item.nota >= Mini.nota) {
            Item.f = fita;
            Insere(&Item,vetor,n);
            
        }    
        if(Min(vetor).f > fita) {
            fita++;
        }
         
        Mini = RetiraMin(vetor, n);
        convertToChar(Mini.f, num);
    
        strcat(block, num);
        strcat(block, txt);
        fileSaida = fopen(block, "ab");
        strcpy(block, "Bloco");
        fwrite(&Mini, sizeof(Mini), 1, fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }
    esvaziarVetor(vetor, &N);
}

void intercalacao_substituicao_selecao(FILE* nome_arquivo) {
    Registro vetor[TAM+1];
    sub(nome_arquivo, vetor, NUM_BLOCK, &N );
}