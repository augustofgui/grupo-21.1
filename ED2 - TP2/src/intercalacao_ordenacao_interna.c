#include "../headers/intercalacao_ordenacao_interna.h"

void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados)
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nIniciando" ANSI_RESET " o processo de intercalacao por ordenacao interna. Aguarde...\n");

    FILE *arquivo_texto, *arquivo_bin;

    arquivo_texto = abrir_arquivo(argv, "r");
    converter_para_binario(arquivo_texto, "arquivo_binario.bin", argv, nro_quantidade);
    fclose(arquivo_texto);

    // ----- Início do Intercalação Ordenação Interna

    clock_t t = clock();
    Estatistica estatistica = {0, 0, 0, 0.0F};

    Fitas fitas = cria_fitas();
    Fita *entrada;
    Fita *saida;
    Fita *aux;

    int contador_fitas, i;

    arquivo_bin = abrir_arquivo("arquivo_binario.bin", "r+b");

    criar_blocos_ordenados(arquivo_bin, nro_quantidade, &fitas, &estatistica, imprimir_dados);

    fitas_rewind(&fitas);

    entrada = fitas.entrada;
    saida = fitas.saida;

    do
    {
        contador_fitas = 0;

        intercalacao_balanceada(entrada, saida, nro_quantidade, entrada[0].tam_ultimo_bloco, &estatistica, imprimir_dados);

        fitas_rewind(&fitas);

        aux = entrada;
        entrada = saida;
        saida = aux;

        for (i = 0; i < NUM_FITAS_ENTRADA; i++)
            contador_fitas += (entrada[i].preenchida) ? 1 : 0;

    } while (contador_fitas != 1);

    printf(ANSI_BOLD ANSI_COLOR_GREEN "\nArquivo ordenado com sucesso!\n" ANSI_RESET);

    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    estatistica.tempo_execucao = tempo_execucao;

    print_estatisticas(estatistica.nro_comparacoes, estatistica.nro_leituras, estatistica.nro_escritas, estatistica.tempo_execucao);

    converter_para_txt(entrada[0].arquivo, "RESULTADO.TXT", nro_quantidade);

    remove_fitas(&fitas);
}

void fitas_rewind(Fitas *fitas)
{
    int i;
    for (i = 0; i < NUM_FITAS_ENTRADA; i++)
        rewind(fitas->entrada[i].arquivo);

    for (i = 0; i < NUM_FITAS_SAIDA; i++)
        rewind(fitas->saida[i].arquivo);
}

void criar_blocos_ordenados(FILE *arquivo_binario, int num_registros, Fitas *fitas, Estatistica *estatistica, bool imprimir_dados)
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " blocos ordenados. Aguarde...\n");

    int numero_leituras_completas = num_registros / TAM_BLOCO;
    int tam_ultima_leitura = num_registros % TAM_BLOCO;

    int i = numero_leituras_completas;
    int j = 0;

    while (i--)
    {
        escreve_na_fita(arquivo_binario, &fitas->entrada[j], TAM_BLOCO, estatistica, imprimir_dados);
        estatistica->nro_leituras += TAM_BLOCO;
        estatistica->nro_escritas += TAM_BLOCO;
        j = (j + 1) % NUM_FITAS_ENTRADA;
    }

    if (tam_ultima_leitura != 0)
    {
        escreve_na_fita(arquivo_binario, &fitas->entrada[j], tam_ultima_leitura, estatistica, imprimir_dados);
        estatistica->nro_leituras += tam_ultima_leitura;
        estatistica->nro_escritas += tam_ultima_leitura;
    }

    printf(ANSI_BOLD ANSI_COLOR_RED "\nBlocos" ANSI_RESET " ordenados com " ANSI_COLOR_GREEN "sucesso!\n" ANSI_RESET);
}

void escreve_na_fita(FILE *arquivo_binario, Fita *fita_destino, int tam, Estatistica *estatistica, bool imprimir_dados)
{
    Registro vetor_reg[TAM_BLOCO];
    int k;

    fread(vetor_reg, sizeof(Registro), tam, arquivo_binario);
    if (imprimir_dados)
        for (k = 0; k < tam; k++)
            PrintFRead(&vetor_reg[k]);

    merge_sort(vetor_reg, 0, tam - 1, estatistica);
    fwrite(vetor_reg, sizeof(Registro), tam, fita_destino->arquivo);
    if (imprimir_dados)
        for (k = 0; k < tam; k++)
            PrintFWrite(&vetor_reg[k]);

    fita_destino->quant_itens += tam;
    fita_destino->tam_ultimo_bloco = tam;
    fita_destino->preenchida = true;
}

void intercalacao_balanceada(Fita *origem, Fita *destino, int nro_registros, int tam_antigo_bloco, Estatistica *estatistica, bool imprimir_dados)
{
    static int count = 0;
    count++;

    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nIniciando" ANSI_RESET " a %d° intercalacao de blocos. Aguarde...\n", count);

    Registro reg_aux;
    Registro mem_interna[TAM_BLOCO];

    int tam_novo_bloco;

    int nro_total_leituras = 0;
    int nro_atual_leituras = 0;
    int nro_atual_escritas = 0;

    int quant_leituras_atual_fita[NUM_FITAS_ENTRADA] = {0};
    int quant_leituras_total_fita[NUM_FITAS_ENTRADA] = {0};
    
    bool fita_completa[NUM_FITAS_ENTRADA] = {false};

    int quant_fitas_escritas = 0;

    int pos_menor = -1;

    int i;
    for (i = 0; i < NUM_FITAS_ENTRADA; i++)
        quant_fitas_escritas += (origem[i].preenchida) ? 1 : 0;

    tam_novo_bloco = tam_antigo_bloco * quant_fitas_escritas;

    int j = 0;

    while (nro_registros > nro_total_leituras)
    {
        for (i = 0; i < quant_fitas_escritas; i++)
            quant_leituras_atual_fita[i] = 0;

        for (i = 0; i < quant_fitas_escritas; i++)
        {
            fread(&reg_aux, sizeof(Registro), 1, origem[i].arquivo);
            mem_interna[i] = reg_aux;
            if (imprimir_dados)
                PrintFRead(&mem_interna[i]);

            estatistica->nro_leituras++;

            quant_leituras_atual_fita[i]++;
            quant_leituras_total_fita[i]++;

            nro_total_leituras++;
            nro_atual_leituras++;
        }

        while (tam_novo_bloco > nro_atual_escritas && nro_registros > nro_atual_escritas)
        {
            pos_menor = acha_posicao_menor_reg(mem_interna, quant_fitas_escritas);
            if (pos_menor == -1)
                break;

            estatistica->nro_comparacoes += quant_fitas_escritas;

            fwrite(&mem_interna[pos_menor], sizeof(Registro), 1, destino[j].arquivo);
            if (imprimir_dados)
                PrintFWrite(&mem_interna[pos_menor]);

            estatistica->nro_escritas++;

            destino[j].quant_itens++;
            nro_atual_escritas++;

            if (!fita_completa[pos_menor])
            {
                fread(&reg_aux, sizeof(Registro), 1, origem[pos_menor].arquivo);
                mem_interna[pos_menor] = reg_aux;
                if (imprimir_dados)
                    PrintFRead(&mem_interna[pos_menor]);

                estatistica->nro_leituras++;

                quant_leituras_atual_fita[pos_menor]++;
                quant_leituras_total_fita[pos_menor]++;

                nro_total_leituras++;
                nro_atual_leituras++;

                if (quant_leituras_atual_fita[pos_menor] == tam_antigo_bloco)
                {
                    fita_completa[pos_menor] = true;
                }
                else if (quant_leituras_atual_fita[pos_menor] == origem[pos_menor].quant_itens)
                {
                    fita_completa[pos_menor] = true;
                }
            }
            else
            {
                if (quant_leituras_atual_fita[pos_menor] == origem[pos_menor].quant_itens)
                    origem[pos_menor].preenchida = false;
                mem_interna[pos_menor].nota = __FLT_MAX__;
            }
        }

        destino[j].preenchida = true;
        destino[j].tam_ultimo_bloco = nro_atual_leituras;

        for (i = 0; i < quant_fitas_escritas; i++)
        {
            origem[i].quant_itens -= quant_leituras_atual_fita[i];
            if (origem[i].quant_itens == 0)
                origem[i].preenchida = false;

            fita_completa[i] = !origem[i].preenchida;
        }

        j = (j + 1) % NUM_FITAS_SAIDA;

        nro_atual_leituras = 0;
        nro_atual_escritas = 0;

        quant_fitas_escritas = 0;
        for (i = 0; i < NUM_FITAS_ENTRADA; i++)
            quant_fitas_escritas += (origem[i].preenchida) ? 1 : 0;
    }

    printf(ANSI_BOLD ANSI_COLOR_RED "\nIntercalacao" ANSI_RESET " realizada com " ANSI_COLOR_GREEN "sucesso!\n" ANSI_RESET);
}

int acha_posicao_menor_reg(Registro *vetor, int tam)
{
    int i, m = -1;
    float menor = __FLT_MAX__;

    for (i = 0; i < tam; i++)
    {
        if (vetor[i].nota < menor)
        {
            m = i;
            menor = vetor[i].nota;
        }
    }

    return m;
}

Fitas cria_fitas()
{
    Fitas fitas_nova;

    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " as fitas para intercalação. Aguarde...\n");

    cria_fitas_tipo(fitas_nova.entrada, NUM_FITAS_ENTRADA, "entrada");
    cria_fitas_tipo(fitas_nova.saida, NUM_FITAS_SAIDA, "saida");

    printf(ANSI_BOLD ANSI_COLOR_RED "\nFitas" ANSI_RESET " criadas com " ANSI_COLOR_GREEN "sucesso!\n" ANSI_RESET);
    return fitas_nova;
}

void remove_fitas(Fitas *fitas)
{
    int i;
    char caminho[TEXT], num[TEXT];

    for( i = 0; i < NUM_FITAS_ENTRADA; i++) {
        sprintf(num, "%02d", i+1);

        fclose(fitas->entrada[i].arquivo);
        string_caminho_fitas("entrada", num, caminho);
        remove(caminho);
    }

    for( i = 0; i < NUM_FITAS_SAIDA; i++) {
        sprintf(num, "%02d", i+1);

        fclose(fitas->saida[i].arquivo);
        string_caminho_fitas("saida", num, caminho);
        remove(caminho);
    }

    remove("arquivo_binario.bin");
}

void cria_fitas_tipo(Fita *vetor, int n, char *tipo)
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " as fitas de %s. Aguarde...", tipo);

    int i;
    char num[TEXT];
    char caminho[TEXT];
    char arquivo[TEXT];

    for (i = 1; i <= n; i++)
    {
        sprintf(num, "%02d", i);

        string_caminho_fitas(tipo, num, caminho);
        string_arquivo_fitas(tipo, num, arquivo);

        vetor[i - 1].arquivo = abrir_arquivo(caminho, "w+b");
        vetor[i - 1].quant_itens = 0;
        vetor[i - 1].tam_ultimo_bloco = TAM_BLOCO;
        vetor[i - 1].preenchida = false;

        printf(ANSI_BOLD "\nFita " ANSI_COLOR_BLUE "%s" ANSI_RESET ": " ANSI_COLOR_GREEN "ok!" ANSI_RESET, arquivo);
    }

    printf(ANSI_BOLD ANSI_COLOR_RED "\nFitas" ANSI_RESET " de %s: " ANSI_COLOR_GREEN "ok!\n" ANSI_RESET, tipo);
}

void string_caminho_fitas(char *tipo, char *num, char *str_out)
{
    char caminho[TEXT];
    char arquivo[TEXT];

    strcpy(caminho, "./fitas/");
    strcat(caminho, tipo);
    strcat(caminho, "/");

    string_arquivo_fitas(tipo, num, arquivo);

    strcat(caminho, arquivo);
    strcpy(str_out, caminho);
}

void string_arquivo_fitas(char *tipo, char *num, char *str_out)
{
    char arquivo[TEXT];

    strcpy(arquivo, tipo);
    strcat(arquivo, "_");

    strcat(arquivo, num);
    strcat(arquivo, ".bin");

    strcpy(str_out, arquivo);
}