#include "../headers/geral.h"
#include "../headers/intercalacao_substituicao_selecao.h"

#define TAM 10 // heap
#define NUM_BLOCK 20 // numero de blocos

int N = TAM;

int comparacoes = 0;
int leituras = 0;
int escritas = 0;

void preencheVetor(Registro* vetor, FILE* fileEntrada) {
    for(int i = 1; i <= TAM; i++) {
         leituras++;
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
         escritas++;
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
     escritas++;
    fwrite(&Mini, sizeof(Mini), 1, fileSaida);
    fclose(fileSaida);

    while (fread(&Item, sizeof(Item), 1, nome_arquivo) == 1) {
         leituras++;
         comparacoes++;
        if(Item.nota < Mini.nota) {
             comparacoes++;
            if(fita == NUM_BLOCK) {
                fita = 1;
            }
            Item.f = fita + 1;
            Insere(&Item,vetor,n);
         }
         comparacoes++;
        if(Item.nota >= Mini.nota) {
            Item.f = fita;
            Insere(&Item,vetor,n);
            
        }
         comparacoes++;
        if(Min(vetor).f > fita) {
            fita++;
        }
         
        Mini = RetiraMin(vetor, n);
        //converter_para_char(Mini.f, num);
    
        strcat(block, num);
        strcat(block, txt);
        fileSaida = fopen(block, "ab");
        strcpy(block, "Bloco");
         escritas++;
        fwrite(&Mini, sizeof(Mini), 1, fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }
    esvaziarVetor(vetor, &N);
}

void intercalacao_substituicao_selecao(char* nome_arquivo, bool imprimir_dados, int nro_quantidade) {

    FILE *ArqTXT;

    ArqTXT = abrir_arquivo(nome_arquivo, "r");
    converter_para_binario(ArqTXT, "arquivo_binario.bin", nome_arquivo, nro_quantidade);
    fclose(ArqTXT);

    clock_t t = clock();

    Registro vetor[TAM+1];
    sub(ArqTXT, vetor, &N );
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;

   if(imprimir_dados){}
    print_estatisticas(comparacoes, comparacoes,  leituras,  escritas, tempo_execucao);
}

////////////////////
////////////////////
////////////////////HEAP
////////////////////
////////////////////

void troca (Registro* A, int n) {
    Registro aux;
    for (int i = 1 ; i < n-1 ; i = (i*2) - 1) {
         comparacoes+=2;
        if(A[i].nota > A[i+1].nota && A[i].f == A[i+1].f) {
        aux = A[i+1];
        A[i+1] = A[i];
        A[i] = aux;  
        }
    }
}

void Refaz (int Esq, int Dir, Registro *A) { 
    int i = Esq;
    int j;
    Registro x;
    j = (i * 2);
    x = A[i];
    while (j <= Dir) {
         comparacoes++;
        if (j < Dir) { 
             comparacoes++;
            if (A[j].nota > A[j+1].nota) {
            j++;
            }    
        }
         comparacoes++;
        if (x.nota <= A[j].nota) { 
            A[i] = x;
        }
        A[i] = A[j];
        i = j; 
        j = i * 2;
    }
} 

void RefazPeloIndice (int Esq, int Dir, Registro *A) { 
    int i = Esq;
    int j;
    Registro x;
    j = (i * 2);
    x = A[i];
    while (j <= Dir) { 
         comparacoes++;
        if (j < Dir) { 
             comparacoes++;
            if (A[j].f > A[j+1].f) {
                j++;
            }       
        }
         comparacoes++;
        if (x.f <= A[j].f) { 
            A[i] = x;
        }         
        A[i] = A[j];
        i = j; 
        j = i * 2;
    }
} 

void Constroi (Registro *A, int *n) {
    int Esq;
    Esq = *n / 2 + 1;
    while (Esq > 1) {
        Esq--;
        Refaz(Esq, *n, A);
    }
} 

void ConstroiPeloIndice (Registro *A, int *n) {
    int Esq;
    Esq = *n /2 + 1 ;

    while (Esq > 1) { 
        Esq--;
        RefazPeloIndice(Esq, *n, A);
    }
} 

Registro Min(Registro *A) {
    return (A[1]); 
}

Registro RetiraMin (Registro *A, int *n) {
    Registro Min;
     comparacoes++;
    if (*n < 1) 
    printf("Erro!!\n");
    else {
        Min = A[1];  
        A[1] = A[*n];  
        (*n)--;
        Refaz(1, *n, A);
        RefazPeloIndice(1,*n,A);
    }
    Constroi(A,n);
    ConstroiPeloIndice(A,n);
    return Min;
}

void Aumenta (int i, double new, Registro *A) { 
    Registro x;
     comparacoes++;
    if (new < A[i].nota) { 
        printf("Erro!!\n");
        return;
    }
    A[i].nota = new;
    while (i > 1 && A[i / 2].nota > A[i].nota) { 
        x = A[i / 2]; 
        A[i / 2] = A[i];  
        A[i] = x;
        i /= 2;
    }
}

void Insere (Registro *x, Registro *A, int *n) {
    (*n)++;
    A[*n] = *x;  
    A[*n].nota = INT_MIN;
    Aumenta(*n, x->nota, A);
    Constroi(A,n);
    ConstroiPeloIndice(A,n);
}

void Imprime (Registro *A, int *n) { 
    int i;
    for (i = 1; i <= *n; i++){
        printf("%f ", A[i].nota);
    }
    printf("\n");
}