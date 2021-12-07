#include "../headers/geral.h"
#include "../headers/quicksort_externo.h"

Estatistica estatistica = {0, 0, 0, 0, 0.0F};

void quicksort_externo_main(char argv[], int nro_quantidade, bool imprimir_dados)
{
    FILE *ArqLi, *ArqEi, *ArqLEs, *ArqTXT;

    ArqTXT = abrir_arquivo(argv, "r");
    converter_para_binario(ArqTXT, "arquivo_binario.bin", argv, nro_quantidade);
    fclose(ArqTXT);

    // ----- Início do Quicksort Externo
    ArqLi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqEi = abrir_arquivo("arquivo_binario.bin", "r+b");
    ArqLEs = abrir_arquivo("arquivo_binario.bin", "r+b");

    print_ordenacao(imprimir_dados);

    clock_t t = clock();
    quicksort_externo(&ArqLi, &ArqEi, &ArqLEs, 1, nro_quantidade, imprimir_dados);
    t = clock() - t;
    estatistica.tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    // ----- Fim do Quicksort Externo

    print_estatisticas(estatistica.nro_comparacoes_ord_interna, estatistica.nro_comparacoes_ord_externa, estatistica.nro_leituras, estatistica.nro_escritas, estatistica.tempo_execucao);

    converter_para_txt(ArqLi, "RESULTADO.TXT", nro_quantidade);
    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    remove("arquivo_binario.bin");
}

void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, bool imprimir_dados)
{
    int i, j;
    TipoArea Area;

    if (Dir - Esq < 1)
        return;

    FAVazia(&Area);

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, imprimir_dados);

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
        if (Area.nro_cels_ocupadas < TAM_AREA - 1)
        {
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);

            InsereItem(&UltLido, &Area);

            continue;
        }

        if (Ls == Es)
        {
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
        }
        else if (Li == Ei)
        {
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);
        }
        else if (OndeLer)
        {
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, imprimir_dados);
        }
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, imprimir_dados);

        estatistica.nro_comparacoes_ord_externa++;
        if (UltLido.nota > Lsup)
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es, imprimir_dados);
            continue;
        }
        estatistica.nro_comparacoes_ord_externa++;
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei, imprimir_dados);
            continue;
        }

        InsereItem(&UltLido, &Area);

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
        RetiraPrimeiro(&Area, &R);
        EscreveMin(ArqEi, R, &Ei, imprimir_dados);
    }
}

void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, bool *OndeLer, bool imprimir_dados)
{
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Registro), SEEK_SET);
    estatistica.nro_leituras++;
    fread(UltLido, sizeof(Registro), 1, *ArqLEs);
    if (imprimir_dados)
        PrintFRead(UltLido);
    (*Ls)--;
    *OndeLer = false;
}

void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, bool *OndeLer, bool imprimir_dados)
{
    estatistica.nro_leituras++;
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
    insertion_sort(Area->array, Area->nro_cels_ocupadas, &estatistica);
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
    insertion_sort(Area->array, Area->nro_cels_ocupadas, &estatistica);
    Area->nro_cels_ocupadas--;
}

void EscreveMax(FILE **ArqLEs, Registro R, int *Es, bool imprimir_dados)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(Registro), SEEK_SET);
    estatistica.nro_escritas++;
    fwrite(&R, sizeof(Registro), 1, *ArqLEs);
    if (imprimir_dados)
        PrintFWrite(&R);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, Registro R, int *Ei, bool imprimir_dados)
{
    estatistica.nro_escritas++;
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
    printf(ANSI_COLOR_YELLOW "Ordenando" ANSI_RESET " o arquivo binário. Aguarde...\n");
    if (imprimir_dados)
        printf("\n");
}