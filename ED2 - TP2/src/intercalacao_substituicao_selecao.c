#include "../headers/geral.h"
#include "../headers/intercalacao_substituicao_selecao.h"
#include "../headers/heap_min.h"

#define TAM 10 // heap
#define NUM_BLOCK 20 // numero de blocos

int N = TAM;

void preencheVetor(Registro* vetor, FILE* fileEntrada) {
    for(int i = 1; i <= TAM; i++) {
        nro_iss_leituras++;
        fread(&vetor[i], sizeof(*vetor), 1, fileEntrada);
    }
    Constroi(vetor, &N);
    Imprime(vetor, &N);
}
/*
void converter_para_char (int num, char* buff) {
        snprintf(buff, sizeof(buff), "%d", num);
}
*/
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
        //converter_para_char(Min.nota, num);
        strcat(block, num);
        strcat(block, bin);
        fileSaida = fopen(block, "ab");
        strcpy(block, "Bloco");
        nro_iss_escritas++;
        fwrite(&Min, sizeof(Min), 1, fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }
}

void sub (FILE* nome_arquivo, Registro* vetor, int* n ) {
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
    nro_iss_escritas++;
    fwrite(&Mini, sizeof(Mini), 1, fileSaida);
    fclose(fileSaida);

    while (fread(&Item, sizeof(Item), 1, nome_arquivo) == 1) {
        nro_iss_leituras++;
        nro_iss_comparacoes++;
        if(Item.nota < Mini.nota) {
            nro_iss_comparacoes++;
            if(fita == NUM_BLOCK) {
                fita = 1;
            }
            Item.f = fita + 1;
            Insere(&Item,vetor,n);
         }
        nro_iss_comparacoes++;
        if(Item.nota >= Mini.nota) {
            Item.f = fita;
            Insere(&Item,vetor,n);
            
        }
        nro_iss_comparacoes++;
        if(Min(vetor).f > fita) {
            fita++;
        }
         
        Mini = RetiraMin(vetor, n);
        //converter_para_char(Mini.f, num);
    
        strcat(block, num);
        strcat(block, txt);
        fileSaida = fopen(block, "ab");
        strcpy(block, "Bloco");
        nro_iss_escritas++;
        fwrite(&Mini, sizeof(Mini), 1, fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }
    esvaziarVetor(vetor, &N);
}

void intercalacao_substituicao_selecao(char* nome_arquivo, bool imprimir_dados) {

    FILE *ArqTXT;

    ArqTXT = abrir_arquivo(nome_arquivo, "r");
    converter_para_binario(ArqTXT, "arquivo_binario.bin", nome_arquivo);
    fclose(ArqTXT);

    clock_t t = clock();

    Registro vetor[TAM+1];
    sub(ArqTXT, vetor, &N );
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;

    print_estatisticas(nro_iss_comparacoes, nro_iss_leituras, nro_iss_escritas, tempo_execucao);
}