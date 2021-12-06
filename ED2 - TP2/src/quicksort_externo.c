#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

int nro_comparacoes = 0;
int nro_leituras = 0;
int nro_escritas = 0;

void quicksort_externo_main(char argv[], int nro_quantidade, bool imprimir_dados)
{
    FILE *ArqLi, *ArqEi, *ArqLEs, *ArqTXT;

    ArqTXT = abrir_arquivo(argv, "r");
    converter_para_binario(ArqTXT, "arquivo_binario.bin", argv);
    fclose(ArqTXT);

    // ----- Início do Quicksort Externo
    ArqLi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqEi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqLEs = abrir_arquivo("arquivo_binario.bin", "r+b");

    print_ordenacao(imprimir_dados);

    clock_t t = clock();
    quicksort_externo(&ArqLi, &ArqEi, &ArqLEs, 1, nro_quantidade, imprimir_dados);
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    // ----- Fim do Quicksort Externo

    print_estatisticas(nro_comparacoes, nro_leituras, nro_escritas, tempo_execucao);

    converter_para_txt(ArqLi, "RESULTADO.TXT");
    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    remove("arquivo_binario.bin");
}

void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, bool imprimir_dados)
{
    int i, j;
    TipoArea Area;

    nro_comparacoes++;
    if (Dir - Esq < 1)
        return;

    FAVazia(&Area);

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, imprimir_dados);

    nro_comparacoes++;
    if (i - Esq < Dir - j)
    {
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i, imprimir_dados);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir, imprimir_dados);
    }
    else
    {
        quicksort_externo(ArqLi, ArqEi, ArqLEs, j, Dir, imprimir_dados);
        quicksort_externo(ArqLi, ArqEi, ArqLEs, Esq, i, imprimir_dados);
    }
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, bool imprimir_dados)
{
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq;
    double Linf = INT_MIN, Lsup = INT_MAX;
    bool OndeLer = true;
    Registro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(Registro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Registro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;

    while (Ls >= Li)
    {
        nro_comparacoes += 2;
        if (Area.nro_cels_ocupadas < TAM_AREA - 1)
        {
            nro_comparacoes++;
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);

            InsereItem(&UltLido, &Area);

            continue;
        }

        nro_comparacoes++;
        if (Ls == Es)
        {
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
        }
        else if (Li == Ei)
        {
            nro_comparacoes++;
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);
        }
        else if (OndeLer)
        {
            nro_comparacoes++;
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
        }
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);

        nro_comparacoes++;
        if (UltLido.nota > Lsup)
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es, imprimir_dados);
            continue;
        }
        nro_comparacoes++;
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei, imprimir_dados);
            continue;
        }

        InsereItem(&UltLido, &Area);

        nro_comparacoes++;
        if (Ei - Esq < Dir - Es)
        {
            RetiraPrimeiro(&Area, &R);
            EscreveMin(ArqEi, R, &Ei, imprimir_dados);
            Linf = R.nota;
        }
        else
        {
            RetiraUltimo(&Area, &R);
            EscreveMax(ArqLEs, R, &Es, imprimir_dados);
            Lsup = R.nota;
        }
    }
    while (Ei <= Es)
    {
        nro_comparacoes++;
        RetiraPrimeiro(&Area, &R);
        EscreveMin(ArqEi, R, &Ei, imprimir_dados);
    }
}

void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, bool *OndeLer, bool imprimir_dados)
{
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Registro), SEEK_SET);
    nro_leituras++;
    fread(UltLido, sizeof(Registro), 1, *ArqLEs);
    if (imprimir_dados)
        PrintFRead(UltLido);
    (*Ls)--;
    *OndeLer = false;
}

void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, bool *OndeLer, bool imprimir_dados)
{
    nro_leituras++;
    fread(UltLido, sizeof(Registro), 1, *ArqLi);
    if (imprimir_dados)
        PrintFRead(UltLido);
    (*Li)++;
    *OndeLer = true;
}

void InsereItem(Registro *UltLido, TipoArea *Area)
{
    Area->array[Area->nro_cels_ocupadas] = *UltLido;
    Area->nro_cels_ocupadas++;
    selection_sort_ascendente(Area->array, Area->nro_cels_ocupadas);
}

void RetiraUltimo(TipoArea *Area, Registro *R)
{
    *R = Area->array[Area->nro_cels_ocupadas - 1];
    Area->array[Area->nro_cels_ocupadas - 1].nota = INT_MAX;
    Area->nro_cels_ocupadas--;
}

void RetiraPrimeiro(TipoArea *Area, Registro *R)
{
    *R = Area->array[0];
    Area->array[0].nota = INT_MAX;
    selection_sort_ascendente(Area->array, Area->nro_cels_ocupadas);
    Area->nro_cels_ocupadas--;
}

void EscreveMax(FILE **ArqLEs, Registro R, int *Es, bool imprimir_dados)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(Registro), SEEK_SET);
    nro_escritas++;
    fwrite(&R, sizeof(Registro), 1, *ArqLEs);
    if (imprimir_dados)
        PrintFWrite(&R);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, Registro R, int *Ei, bool imprimir_dados)
{
    fwrite(&R, sizeof(Registro), 1, *ArqEi);
    if (imprimir_dados)
        PrintFWrite(&R);
    (*Ei)++;
}

void FAVazia(TipoArea *Area)
{
    for (int i = 0; i < TAM_AREA; i++)
        Area->array[i].nota = INT_MAX;

    Area->nro_cels_ocupadas = 0;
}

void PrintArea(TipoArea Area)
{
    printf("\n     - Area -\n");
    for (int i = 0; i < TAM_AREA; i++)
        printf("%08ld %05.1f%s\n", Area.array[i].inscricao, Area.array[i].nota, Area.array[i].estado_cidade_curso);
    printf("Nº de cels ocupadas: %d\n\n", Area.nro_cels_ocupadas);
}

void print_ordenacao(bool imprimir_dados)
{
    printf(ANSI_COLOR_YELLOW"Ordenando"ANSI_RESET" o arquivo binário. Aguarde...\n");
    if (imprimir_dados)
        printf("\n");
}