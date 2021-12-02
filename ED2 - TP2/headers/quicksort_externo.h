#define INT_MIN  (-2147483648)
#define INT_MAX   (2147483647)

#define TAM_AREA 20

typedef struct {
    Registro array[TAM_AREA];
    int nro_cels_ocupadas;
} TipoArea;

void quicksort_externo_main(char argv[], int nro_quantidade);
void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j);
void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, short *OndeLer);
void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, short *OndeLer);
void InserirArea(TipoArea *Area, Registro *UltLido, int *NRArea);
void EscreveMax(FILE **ArqLEs, Registro R, int *Es);
void EscreveMin(FILE **ArqEi, Registro R, int *Ei);
void RetiraMax(TipoArea *Area, Registro *R, int *NRArea);
void RetiraMin(TipoArea *Area, Registro *R, int *NRArea);
void FAVazia(TipoArea* Area);
void RetiraUltimo(TipoArea *Area, Registro *R);
void RetiraPrimeiro(TipoArea *Area, Registro *R);
void InsereItem(Registro *UltLido, TipoArea *Area);