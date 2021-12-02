#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

void quicksort_externo_main(char argv[], int nro_quantidade)
{
    FILE *ArqLi, *ArqEi, *ArqLEs, *ArqTXT, *ArqBinario;

    ArqTXT = abrir_arquivo(argv, "r");

    printf("Convertendo o arquivo .txt para binário. Aguarde...\n");
    ArqBinario = converter_para_binario(ArqTXT, "arquivo_binario.bin");

    fclose(ArqBinario);
    fclose(ArqTXT);

    ArqLi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqEi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqLEs = abrir_arquivo("arquivo_binario.bin", "r+b");

    printf("Ordenando o arquivo binário. Aguarde...\n");
    quicksort_externo(&ArqLi, &ArqEi, &ArqLEs, 1, nro_quantidade);

    printf("Convertendo o arquivo binário para .txt. Aguarde...\n");
    rewind(ArqLi);
    converter_para_txt(ArqLi, "PROVAO.txt");

    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    remove("arquivo_binario.bin");
}

void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir)
{
    int i, j;
    TipoArea Area;

    if (Dir - Esq < 1)
        return;

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
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = INT_MIN, Lsup = INT_MAX;
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
    }
    while (Ei <= Es)
    {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }
}

void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, short *OndeLer)
{
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Registro), SEEK_SET);
    fread(UltLido, sizeof(Registro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = 0;
}

void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, short *OndeLer)
{
    fread(UltLido, sizeof(Registro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = 1;
}

void InserirArea(TipoArea *Area, Registro *UltLido, int *NRArea)
{
    InsereItem(UltLido, Area);
    *NRArea = Area->nro_cels_ocupadas;
}

void InsereItem(Registro *UltLido, TipoArea *Area)
{
    Area->array[Area->nro_cels_ocupadas] = *UltLido;
    Area->nro_cels_ocupadas++;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

void RetiraUltimo(TipoArea *Area, Registro *R)
{
    *R = Area->array[Area->nro_cels_ocupadas - 1];
    Area->array[Area->nro_cels_ocupadas - 1].nota = MAX_NOTA;
    Area->nro_cels_ocupadas--;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

void RetiraPrimeiro(TipoArea *Area, Registro *R)
{
    *R = Area->array[0];
    Area->array[0].nota = MAX_NOTA;
    Area->nro_cels_ocupadas--;
    merge_sort(Area->array, 0, TAM_AREA - 1);
}

void EscreveMax(FILE **ArqLEs, Registro R, int *Es)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(Registro), SEEK_SET);
    fwrite(&R, sizeof(Registro), 1, *ArqLEs);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, Registro R, int *Ei)
{
    fwrite(&R, sizeof(Registro), 1, *ArqEi);
    (*Ei)++;
}

void RetiraMax(TipoArea *Area, Registro *R, int *NRArea)
{
    RetiraUltimo(Area, R);
    *NRArea = Area->nro_cels_ocupadas;
}

void RetiraMin(TipoArea *Area, Registro *R, int *NRArea)
{
    RetiraPrimeiro(Area, R);
    *NRArea = Area->nro_cels_ocupadas;
}

void FAVazia(TipoArea *Area)
{
    for (int i = 0; i < TAM_AREA; i++)
        Area->array[i].nota = MAX_NOTA;

    Area->nro_cels_ocupadas = 0;
}

void PrintArea(TipoArea *Area)
{
    for (int i = 0; i < TAM_AREA; i++)
        printf("%ld %lf%s\n", Area->array[i].inscricao, Area->array[i].nota, Area->array[i].estado_cidade_curso);
    printf("Nº de cels ocupadas: %d\n", Area->nro_cels_ocupadas);
}