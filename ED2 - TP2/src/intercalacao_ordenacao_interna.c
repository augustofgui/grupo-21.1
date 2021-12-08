#include "../headers/intercalacao_ordenacao_interna.h"

// ----- Função principal que organiza e executa a Intercalação com Ordenação Interna.
void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados)
{      
    // ----- Printf de início de execução.
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nIniciando" ANSI_RESET " o processo de intercalacao por ordenacao interna. Aguarde...\n");

    // ----- Arquivos de entrada.
    FILE *arquivo_texto, *arquivo_bin;

    // ----- Conversão do arquivo .txt para .bin.
    arquivo_texto = abrir_arquivo(argv, "r");
    converter_para_binario(arquivo_texto, "arquivo_binario.bin", argv, nro_quantidade);
    fclose(arquivo_texto);

    // ----- Início do Intercalação Ordenação Interna.

    // ----- Início da contagem de tempo.
    clock_t t = clock();

    // ----- Criada tabela das estatisticas de execução.
    Estatistica estatistica = {0, 0, 0, 0, 0.0F};

    // ----- Declaração das fitas.
    Fitas fitas = cria_fitas();

    // ----- Vetores auxiliares de fitas.
    Fita *entrada;
    Fita *saida;
    Fita *aux;

    // ----- Contadores.
    int contador_fitas, i;

    // ----- Tenta abrir o arquivo binário para leitura.
    arquivo_bin = abrir_arquivo("arquivo_binario.bin", "r+b");

    // ----- Cria, ordena e escreve os blocos ordenados nas fitas de entrada.
    criar_blocos_ordenados(arquivo_bin, nro_quantidade, &fitas, &estatistica, imprimir_dados);

    // ----- Executa rewind em todas as fita.
    fitas_rewind(&fitas);

    // ----- Inicializa os vetores auxiliares com
    // ----- os vetores respectivos de fitas.
    entrada = fitas.entrada;
    saida = fitas.saida;

    // ----- Realiza a intercalação, invertendo as fitas
    // ----- de saida e entrada até que a apenas
    // ----- a primeira fita esteja preenchida.
    do
    {   
        // Inicia o contador de fitas preenchidas em 0.
        contador_fitas = 0;

        // Realiza a intercalação balanceada, recebendo 2 vetores de Fita.
        intercalacao_balanceada(entrada, saida, nro_quantidade, entrada[0].tam_ultimo_bloco, &estatistica, imprimir_dados);

        // Reinicia os contadores de fita.
        fitas_rewind(&fitas);

        // Troca as fitas de entrada e saida.
        // A de saida vira de entrada.
        // E a entrada vira de saida.
        aux = entrada;
        entrada = saida;
        saida = aux;

        // Conta quantas fitas estão preenchidas.
        for (i = 0; i < NUM_FITAS_ENTRADA; i++)
            contador_fitas += (entrada[i].preenchida) ? 1 : 0;
    
    // Continua enquanto não tiver restando apenas 1 fita
    // preenchida, com todos os registro ordenados.
    } while (contador_fitas != 1);

    // Printf de conclusão da ordenação interna.
    printf(ANSI_BOLD ANSI_COLOR_GREEN "\nArquivo ordenado com sucesso!\n" ANSI_RESET);
    // Printa os valores de resultado
    if(imprimir_dados)
        print_resultado_ordenacao(entrada[0].arquivo);

    // Para o contador de tempo e calcula os segundos passados.
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    // Leva os segundos para a tabela de estatistica.
    estatistica.tempo_execucao = tempo_execucao;

    // Printa a tabela de estatistica com os valores adiquiridos.
    print_estatisticas(estatistica.nro_comparacoes_ord_externa, estatistica.nro_comparacoes_ord_interna, estatistica.nro_leituras, estatistica.nro_escritas, estatistica.tempo_execucao);

    // Covnerte a fita da ultima intercalação de .bin para .txt.
    converter_para_txt(entrada[0].arquivo, "RESULTADO.TXT", nro_quantidade);

    // Fecha e remove as fitasdo programa.
    remove_fitas(&fitas);
}

// ----- Cria, ordena e escreve os blocos ordenados.
void criar_blocos_ordenados(FILE *arquivo_binario, int num_registros, Fitas *fitas, Estatistica *estatistica, bool imprimir_dados)
{   
    // ----- Printf de inicio de execução
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " blocos ordenados. Aguarde...\n");

    // ----- Calcula o numero de blocos completos de registros no arquivo
    int numero_leituras_completas = num_registros / TAM_BLOCO;

    // ----- Calcula caso existem registros restantes, formando um bloco incompleto
    int tam_ultima_leitura = num_registros % TAM_BLOCO;

    // Contadores
    int i = numero_leituras_completas;  // Contador de leituras
    int j = 0;                          // Contador que cicla entre fitas

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

void intercalacao_balanceada(Fita *origem, Fita *destino, int nro_registros, int tam_antigo_bloco, Estatistica * estatistica, bool imprimir_dados)
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

            estatistica->nro_comparacoes_ord_externa += quant_fitas_escritas;

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
