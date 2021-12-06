#include "../headers/intercalacao_ordenacao_interna.h"

void intercalacao_ordenacao_interna(char argv[], int nro_quantidade, bool imprimir_dados) { 
    FILE * arquivo_texto, * arquivo_bin;

    arquivo_texto = abrir_arquivo(argv, "r");
    converter_para_binario(arquivo_texto, "arquivo_binario.bin", argv);
    fclose(arquivo_texto);

    // ----- Início do Intercalação Ordenação Interna

    clock_t t = clock();

    Fitas fitas = cria_fitas();

    arquivo_bin = abrir_arquivo("arquivo_binario.bin", "r+b");

    criar_blocos_ordenados(arquivo_bin, nro_quantidade, fitas, imprimir_dados);

    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;

}

void criar_blocos_ordenados(FILE * arquivo_binario, int num_registros, Fitas fitas, bool imprimir_dados) {
    printf(ANSI_BOLD ANSI_COLOR_YELLOW"\nCriando"ANSI_RESET" blocos ordenados. Aguarde...\n");

    Registro vetor_reg[TAM_BLOCO];

    int numero_leituras_completas = num_registros / TAM_BLOCO;
    int tam_ultima_leitura = num_registros % TAM_BLOCO;
    
    int i = numero_leituras_completas;
    int j = 0;
    int k;
    
    while(i--){
        fread(vetor_reg, sizeof(Registro), TAM_BLOCO, arquivo_binario);
        if (imprimir_dados)
            for( k = 0; k < TAM_BLOCO; k++ )
                PrintFRead(&vetor_reg[k]);

        selection_sort_ascendente(vetor_reg, TAM_BLOCO);
        fwrite(vetor_reg, sizeof(Registro), TAM_BLOCO, fitas.entrada[j].arquivo);
        fitas.entrada[j].quant_itens += TAM_BLOCO;
        fitas.entrada[j].tam_ultimo_bloco = TAM_BLOCO;

        if (imprimir_dados)
            for( k = 0; k < TAM_BLOCO; k++ )
                PrintFWrite(&vetor_reg[k]);

        j = (j + 1) % NUM_FITAS_ENTRADA;
    }

    if(tam_ultima_leitura != 0) {
        fread(vetor_reg, sizeof(Registro), tam_ultima_leitura, arquivo_binario);
        if (imprimir_dados)
            for( k = 0; k < tam_ultima_leitura; k++ )
                PrintFRead(&vetor_reg[k]);

        selection_sort_ascendente(vetor_reg, tam_ultima_leitura);
        fwrite(vetor_reg, sizeof(Registro), tam_ultima_leitura, fitas.entrada[j].arquivo);
        if (imprimir_dados)
            for( k = 0; k < tam_ultima_leitura; k++ )
                PrintFWrite(&vetor_reg[k]);

        fitas.entrada[j].quant_itens += tam_ultima_leitura;
        fitas.entrada[j].tam_ultimo_bloco = tam_ultima_leitura;
    }

    printf(ANSI_BOLD ANSI_COLOR_RED"\nBlocos"ANSI_RESET" ordenados com sucesso!\n");
}

Fitas cria_fitas() {
    Fitas fitas_nova;

    printf(ANSI_BOLD ANSI_COLOR_YELLOW"\nCriando"ANSI_RESET" as fitas para intercalação. Aguarde...\n");

    cria_fitas_entrada(fitas_nova.entrada);
    cria_fitas_saida(fitas_nova.saida);    

    printf(ANSI_BOLD ANSI_COLOR_RED"\nFitas"ANSI_RESET" criadas com sucesso!\n");
    return fitas_nova;
}

void cria_fitas_entrada(Fita * vetor) {
    printf(ANSI_BOLD ANSI_COLOR_YELLOW"\nCriando"ANSI_RESET" as fitas de entrada. Aguarde...");

    int i;
    char num[TEXT];
    char caminho[TEXT];
    char arquivo[TEXT];

    for( i = 1; i <= NUM_FITAS_ENTRADA; i++ ) {
        sprintf(num, "%02d", i);

        strcpy(caminho, "./fitas/entrada/");
        strcpy(arquivo, "entrada_");

        strcat(arquivo, num);
        strcat(arquivo, ".bin");
        strcat(caminho, arquivo);

        vetor[i-1].arquivo = abrir_arquivo(caminho, "w+b");
        vetor[i-1].quant_itens = 0;
        vetor[i-1].tam_ultimo_bloco = TAM_BLOCO;

        printf(ANSI_BOLD"\nFita "ANSI_COLOR_BLUE"%s"ANSI_RESET ": " ANSI_COLOR_GREEN "ok!"ANSI_RESET, arquivo);
    }

    printf(ANSI_BOLD ANSI_COLOR_RED"\nFitas"ANSI_RESET" de entrada: " ANSI_COLOR_GREEN "ok!\n"ANSI_RESET);

}

void cria_fitas_saida(Fita * vetor) {
    printf(ANSI_BOLD ANSI_COLOR_YELLOW"\nCriando"ANSI_RESET" as fitas de saida. Aguarde...");

    int i;
    char num[TEXT];
    char caminho[TEXT];
    char arquivo[TEXT];

    for( i = 1; i <= NUM_FITAS_SAIDA; i++ ) {
        sprintf(num, "%02d", i);

        strcpy(caminho, "./fitas/saida/");
        strcpy(arquivo, "saida_");

        strcat(arquivo, num);
        strcat(arquivo, ".bin");
        strcat(caminho, arquivo);

        vetor[i-1].arquivo = abrir_arquivo(caminho, "w+b");
        vetor[i-1].quant_itens = 0;
        vetor[i-1].tam_ultimo_bloco = TAM_BLOCO;

        printf(ANSI_BOLD"\nFita "ANSI_COLOR_BLUE"%s"ANSI_RESET ": " ANSI_COLOR_GREEN "ok!"ANSI_RESET, arquivo);
    }
    
    printf(ANSI_BOLD ANSI_COLOR_RED"\nFitas"ANSI_RESET" de saida: " ANSI_COLOR_GREEN "ok!\n"ANSI_RESET);
}
