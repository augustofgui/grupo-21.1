#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

void quicksort_externo_main(){
   //
}

void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
    int i, j;
    Registro *Area = malloc(Registro*)(TAM_AREA * sizeof(Registro));

    if (Dir - Esq < 1) return;
    FAVazia(&Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
    if (i - Esq < Dir - j){
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir);
    }
    else{
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Registro *Area, int Esq, int Dir, int *i, int *j){
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = 1;
    Registro UltLido, R;
    
    fseek(*ArqLi, (Li - 1) * sizeof(Registro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Registro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;

    while (Ls >= Li){
        if (NRArea < TAM_AREA - 1){
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }

        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);

        if (UltLido.nota > Lsup){
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if (UltLido.nota < Linf){
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }

        InserirArea(Area, &UltLido, &NRArea);
        
        if (Ei - Esq < Dir - Es){
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        }
        else{
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }

        while (Ei <= Es){
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
        }
    }
}

void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, short *OndeLer){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Registro), SEEK_SET);
    fread (UltLido, sizeof(Registro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = 0;
}

void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, short *OndeLer){
    fread(UltLido, sizeof(Registro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = 1;
}

void InserirArea(Registro *Area, Registro *UltLido, int *NRArea){
    InsereItem(*UltLido, Area);
    *NRArea = ObterNumCelOcupadas(Area);
}

void EscreveMax(FILE **ArqLEs, Registro R, int *Es){
    fseek(*ArqLEs, (*ES - 1) * sizeof(Registro), SEEK_SET);
    fwrite(&R, sizeof(Registro), 1, *ArqLEs);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, Registro R, int *Ei){
    fwrite(&R, sizeof(Registro), 1, *ArqEi);
    (*Ei)++;
}

void RetiraMax(Registro *Area, Registro *R, int *NRArea){
    retira_ultimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void RetiraMin(Registro *Area, Registro *R, int *NRArea){
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}