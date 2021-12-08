#include "../headers/intercalacao_substituicao_selecao.h"

#define TAM 10       // heap
#define NUM_BLOCK 20 // numero de blocos


void intercalacao_substituicao_selecao(char argv[], int nro_quantidade, bool imprimir_dados)
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
    criar_blocos_ordenados_heap(arquivo_bin, nro_quantidade, &fitas, &estatistica, imprimir_dados);

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


void criar_blocos_ordenados_heap(FILE *arquivo_binario, int num_registros, Fitas *fitas, Estatistica *estatistica, bool imprimir_dados)
{
    Registro mem_interna[TAM_BLOCO];
    rewind(arquivo_binario);

    int num_reg_marcados = 0;
    int num_total_reg_lidos = 0;
    int num_total_reg_escritos = 0;
    int num_atual_registro_escritos = 0;
    
    int tam_ultimo_bloco;

    Registro anterior;

    int k, i, j = 0;
    // ----- Printf de inicio de execução
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " blocos ordenados. Aguarde...\n");

    fread(mem_interna, sizeof(Registro), TAM_BLOCO, arquivo_binario);
    if (imprimir_dados)
        for (k = 0; k < TAM_BLOCO; k++)
            PrintFRead(&mem_interna[k]);
    
    num_total_reg_lidos += TAM_BLOCO;

    for (i = 0; i < TAM_BLOCO; i++)
        mem_interna[i].f = 0;

    while(num_total_reg_lidos < num_registros){
        num_reg_marcados = 0;
        num_atual_registro_escritos = 0;
        for (i = 0; i < TAM_BLOCO; i++)
            mem_interna[i].f = 0;

        while(num_reg_marcados < TAM_BLOCO && num_total_reg_lidos < num_registros) {
            heapsort(mem_interna, TAM_BLOCO, estatistica);

            anterior = mem_interna[0];

            fwrite(&mem_interna[0], sizeof(Registro), 1, fitas->entrada[j].arquivo);
            if (imprimir_dados) // Imprime instrução de fwrite caso o programa seja iniciado com -P.
                PrintFWrite(&mem_interna[0]);

            num_atual_registro_escritos++;
            num_total_reg_escritos++;

            fread(&mem_interna[0], sizeof(Registro), 1, arquivo_binario);
            if (imprimir_dados)
                PrintFRead(&mem_interna[0]);
            
            num_total_reg_lidos++;
            mem_interna[0].f = 0;

            if (mem_interna[0].nota < anterior.nota)
            {
                num_reg_marcados++;
                mem_interna[0].f = 1;
            }
        }

        fitas->entrada[j].quant_itens += num_atual_registro_escritos;
        fitas->entrada[j].tam_ultimo_bloco = num_atual_registro_escritos;
        fitas->entrada[j].preenchida = true;

        j = (j + 1) % NUM_FITAS_ENTRADA;
    }

    for (i = 0; i < TAM_BLOCO; i++)
        mem_interna[i].f = 0;
    
    heapsort(mem_interna, TAM_BLOCO, estatistica);

    fwrite(&mem_interna, sizeof(Registro), TAM_BLOCO, fitas->entrada[j].arquivo);
    if (imprimir_dados)
        for (k = 0; k < TAM_BLOCO; k++)
            PrintFWrite(&mem_interna[k]);

    fitas->entrada[j].quant_itens += TAM_BLOCO;
    fitas->entrada[j].tam_ultimo_bloco = TAM_BLOCO;
    fitas->entrada[j].preenchida = true;

    printf(ANSI_BOLD ANSI_COLOR_RED "\nBlocos" ANSI_RESET " ordenados com " ANSI_COLOR_GREEN "sucesso!\n" ANSI_RESET);
}