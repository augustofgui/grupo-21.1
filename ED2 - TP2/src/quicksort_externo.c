#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

void quicksort_externo_main(char argv[], int nro_quantidade)
{
    FILE *ArqLi, *ArqEi, *ArqLEs;
    ArqLi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqEi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqLEs = abrir_arquivo("arquivo_binario.bin", "r+b");
    quicksort_externo(&ArqLi, &ArqEi, &ArqLEs, 1, nro_quantidade);
    rewind(ArqLi);
    converter_para_txt(ArqLi, "arquivo_texto.txt");
}

void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir)
{
    int i, j;

    if (Dir - Esq < 1)
        return;

    TipoArea Area;
    FAVazia(&Area);

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);

    if (i - Esq < Dir - j)
    {
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir);
    }
    else
    {
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j)
{
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = 1;
    Registro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(Registro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Registro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;

    while (Ls >= Li)
    {
        if (NRArea < TAM_AREA - 1)
        {
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }

        // ------ OK ATÉ AQUI ------ //

        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);

        if (UltLido.nota > Lsup)
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }

        InserirArea(&Area, &UltLido, &NRArea);

        if (Ei - Esq < Dir - Es)
        {
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        }
        else
        {
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }

        while (Ei <= Es)
        {
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
        }
    }
}

// ----- OK ----- //
void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, short *OndeLer)
{
    fseek(*ArqLEs, ((*Ls - 1) * sizeof(Registro)), SEEK_SET);
    fread(UltLido, sizeof(Registro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = 0;
}

// ----- OK ----- //
void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, short *OndeLer)
{
    fread(UltLido, sizeof(Registro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = 1;
}

// ----- OK ----- //
void InserirArea(TipoArea *Area, Registro *UltLido, int *NRArea)
{
    InsereItem(UltLido, Area);
    *NRArea = Area->nro_cels_ocupadas;
}

// ----- OK ----- //
void InsereItem(Registro *UltLido, TipoArea *Area){
    Area->array[Area->nro_cels_ocupadas] = *UltLido;
    Area->nro_cels_ocupadas++;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

// ----- OK ----- //
void RetiraUltimo(TipoArea *Area, Registro *R){
    *R = Area->array[Area->nro_cels_ocupadas - 1];
    Area->array[Area->nro_cels_ocupadas - 1].nota = 99999.99;
    Area->nro_cels_ocupadas--;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

// ----- OK ----- //
void RetiraPrimeiro(TipoArea *Area, Registro *R){
    *R = Area->array[0];
    Area->array[0].nota = 99999.99;
    Area->nro_cels_ocupadas--;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

// ----- OK ----- //
void EscreveMax(FILE **ArqLEs, Registro R, int *Es)
{
    fseek(*ArqLEs, ((*Es - 1) * sizeof(Registro)), SEEK_SET);
    fwrite(&R, sizeof(Registro), 1, *ArqLEs);
    (*Es)--;
}

// ----- OK ----- //
void EscreveMin(FILE **ArqEi, Registro R, int *Ei)
{
    fwrite(&R, sizeof(Registro), 1, *ArqEi);
    (*Ei)++;
}

// ----- OK ----- //
void RetiraMax(TipoArea *Area, Registro *R, int *NRArea)
{
    RetiraUltimo(Area, R);
    *NRArea = Area->nro_cels_ocupadas;
}

// ----- OK ----- //
void RetiraMin(TipoArea *Area, Registro *R, int *NRArea)
{
    RetiraPrimeiro(Area, R);
    *NRArea = Area->nro_cels_ocupadas;
}

// ----- OK ----- //
void FAVazia(TipoArea* Area){
    for (int i = 0; i < TAM_AREA; i++)
        Area->array[i].nota = 99999.99;
    Area->nro_cels_ocupadas = 0;
}