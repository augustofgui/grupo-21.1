#include "../headers/fita.h"

// ----- Função que cria e retorna uma cópia
// ----- de um conjunto novo de fitas.
Fitas cria_fitas()
{
    // ----- Declaração Variáveis.
    Fitas fitas_nova;

    // ----- Printf de inicio de execução.
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " as fitas para intercalação. Aguarde...\n");

    // ----- Chamada a função que cria um vetor de fitas
    // ----- de fitas, enviando o tamanho definido, e o
    // ----- tipo da fita a ser criada, podendo ser:
    // ----- "entrada" ou "saida".
    cria_fitas_tipo(fitas_nova.entrada, NUM_FITAS_ENTRADA, "entrada");
    cria_fitas_tipo(fitas_nova.saida, NUM_FITAS_SAIDA, "saida");

    // ----- Printf de fim de execução.
    printf(ANSI_BOLD ANSI_COLOR_RED "\nFitas" ANSI_RESET " criadas com " ANSI_COLOR_GREEN "sucesso!\n" ANSI_RESET);

    // ----- Retorno do conjunto de fitas criado.
    return fitas_nova;
}

// ----- Cria e retorna um Fita criada a
// ----- partir dos valores passados.
Fita nova_fita(char * caminho, int quant_itens, int tam_ultimo_bloco, bool preenchida)
{   
    // ----- Declaração Variáveis
    Fita nova;

    // ----- Insere na nova fita os valores passados
    nova.arquivo = abrir_arquivo(caminho, "w+b"); // Tenta abrir arquivo pelo caminho
    nova.quant_itens = quant_itens;
    nova.tam_ultimo_bloco = tam_ultimo_bloco;
    nova.preenchida = preenchida;

    // ----- Retorna a nova fita
    return nova;
}

// ----- Função que executa rewind em todas
// ----- fitas do conjunto.
void remove_fitas(Fitas *fitas)
{
    // ----- Declaração Variáveis
    int i;
    char caminho[TEXT], num[TEXT]; // strings.

    // ----- Percorre todas as fitas de entrada
    // ----- tentando fechar o arquivo indicado
    // ----- pelo ponteiro.
    for (i = 0; i < NUM_FITAS_ENTRADA; i++)
    {
        sprintf(num, "%02d", i + 1); // Transforma o valor de i em string.

        fclose(fitas->entrada[i].arquivo); // Fecha o ponteiro do arquivo.

        // ----- Recupera o caminho que a fita ocupa.
        string_caminho_fitas("entrada", num, caminho);
        remove(caminho); // Remove o arquivo de fita usando o caminho recuperado.
    }

    // ----- Percorre todas as fitas de saida
    // ----- tentando fechar o arquivo indicado
    // ----- pelo ponteiro.
    for (i = 0; i < NUM_FITAS_SAIDA; i++)
    {
        sprintf(num, "%02d", i + 1); // Transforma o valor de i em string.

        fclose(fitas->saida[i].arquivo); // Fecha o ponteiro do arquivo.

        // ----- Recupera o caminho que a fita ocupa.
        string_caminho_fitas("saida", num, caminho);
        remove(caminho); // Remove o arquivo de fita usando o caminho recuperado.
    }

    // ----- Remove o arquivo temporário de PROVÃO.txt
    // ----- que foi traduzido para binário.
    remove("arquivo_binario.bin");
}

// ----- Executa rewind em todas as fitas do conjunto.
void fitas_rewind(Fitas *fitas)
{
    int i; // Contador.

    // ----- Percorre todas fitas de entrada e
    // ----- saida e executa rewind em cada.
    for (i = 0; i < NUM_FITAS_ENTRADA; i++)
        rewind(fitas->entrada[i].arquivo);

    for (i = 0; i < NUM_FITAS_SAIDA; i++)
        rewind(fitas->saida[i].arquivo);
}

// ----- Cria um vetor de fitas de tamanho n
// ----- do tipo desejado, podendo ser de
// ----- "entrada" ou "saida".
void cria_fitas_tipo(Fita *vetor, int n, char *tipo)
{
    // ----- Printf de início de execução.
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "\nCriando" ANSI_RESET " as fitas de %s. Aguarde...", tipo);

    // ----- Declaração Variáveis.
    int i;
    char num[TEXT];     // string.
    char caminho[TEXT]; // string.
    char arquivo[TEXT]; // string.

    // ----- Em cada posição do vetor, tenta
    // ----- abrir um arquivo pelo caminho criado.
    // ----- Inicializa as variáveis da fita criada.
    for (i = 1; i <= n; i++)
    {   
        // ----- Transforma o i em string.
        sprintf(num, "%02d", i);

        // ----- Recupera o nome e o caminho do arquivo da fita.
        string_caminho_fitas(tipo, num, caminho);
        string_arquivo_fitas(tipo, num, arquivo);

        // ----- Cria e insere no vetor a nova fita.
        vetor[i - 1] = nova_fita(caminho, 0, TAM_BLOCO, false);

        // ----- Printf de confirmação do processo de criação de uma fita.
        printf(ANSI_BOLD "\nFita " ANSI_COLOR_BLUE "%s" ANSI_RESET ": " ANSI_COLOR_GREEN "ok!" ANSI_RESET, arquivo);
    }

    // ----- Printf de fim de execução.
    printf(ANSI_BOLD ANSI_COLOR_RED "\nFitas" ANSI_RESET " de %s: " ANSI_COLOR_GREEN "ok!\n" ANSI_RESET, tipo);
}

void escreve_na_fita(FILE *arquivo_binario, Fita *fita_destino, int tam, Estatistica *estatistica, bool imprimir_dados)
{   
    // ----- Declaração Variáveis.
    int k; 
    Registro vetor_reg[TAM_BLOCO]; // Vetor de memória interna.

    // ----- Lê tam Registros do arquivo.
    fread(vetor_reg, sizeof(Registro), tam, arquivo_binario);
    if (imprimir_dados) // Imprime instrução de fread caso o programa seja iniciado com -P.
        for (k = 0; k < tam; k++)
            PrintFRead(&vetor_reg[k]);

    // ----- Ordena o vetor em memória principal, usando o método de merge sort.
    heapsort(vetor_reg, tam, estatistica);

    // ----- Escreve na fita destino os registros lidos.
    fwrite(vetor_reg, sizeof(Registro), tam, fita_destino->arquivo);
    if (imprimir_dados) // Imprime instrução de fwrite caso o programa seja iniciado com -P.
        for (k = 0; k < tam; k++)
            PrintFWrite(&vetor_reg[k]);

    // ----- Define as outras informações afetadas pela
    // ----- inserção de um novo elemento na fita.
    fita_destino->quant_itens += tam;
    fita_destino->tam_ultimo_bloco = tam;
    fita_destino->preenchida = true;
}

// ----- Cria string de caminho da fita e a retorna em str_out.
void string_caminho_fitas(char *tipo, char *num, char *str_out)
{
    char caminho[TEXT]; // string com o caminho do arquivo.
    char arquivo[TEXT]; // string com o nome do arquivo.

    // ----- Copia para a string caminho a base
    // ----- do path do arquivo de fita.
    // ----- "./fitas/"
    strcpy(caminho, "./fitas/");
    strcat(caminho, tipo);
    strcat(caminho, "/");

    // ----- Recebe em arquivo, o nome do arquivo
    // ----- de acordo com seu num e seu tipo.
    string_arquivo_fitas(tipo, num, arquivo);

    // ----- Concatena no caminho, o nome do arquivo.
    // ----- "./fitas/tipo_XX.bin"
    strcat(caminho, arquivo);

    // ----- Reliza a cópia para str_out, retornando o caminho criado.
    strcpy(str_out, caminho);
}

// ----- Cria string com o nome da fita e a retorna em str_out.
void string_arquivo_fitas(char *tipo, char *num, char *str_out)
{
    char arquivo[TEXT]; // string com o nome do arquivo.

    // ----- Copia para arquivo a base do nome do arquivo.
    // ----- "tipo_"
    strcpy(arquivo, tipo);
    strcat(arquivo, "_");

    strcat(arquivo, num); // Concatena a string contendo o numero
    strcat(arquivo, ".bin"); // Concatena a extensão do arquivo

    // ----- Copia para str_out o nome do arquivo.
    strcpy(str_out, arquivo);
}