#include "../headers/geral.h"
#include "../headers/heap_min.h"

void troca (Registro* A, int n) {
    Registro aux;
    for (int i = 1 ; i < n-1 ; i = (i*2) - 1) {
        nro_iss_comparacoes+=2;
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
        nro_iss_comparacoes++;
        if (j < Dir) { 
            nro_iss_comparacoes++;
            if (A[j].nota > A[j+1].nota) {
            j++;
            }    
        }
        nro_iss_comparacoes++;
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
        nro_iss_comparacoes++;
        if (j < Dir) { 
            nro_iss_comparacoes++;
            if (A[j].f > A[j+1].f) {
                j++;
            }       
        }
        nro_iss_comparacoes++;
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
    nro_iss_comparacoes++;
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
    nro_iss_comparacoes++;
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