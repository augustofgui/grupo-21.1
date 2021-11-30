#define INT_MIN  (-2147483648)
#define INT_MAX   (2147483647)

#define TAM_AREA 20

void quicksort_externo_main(char argv[], int nro_quantidade);
void quicksort_externo(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Registro *Area, int Esq, int Dir, int *i, int *j);
void LeSup(FILE **ArqLEs, Registro *UltLido, int *Ls, short *OndeLer);
void LeInf(FILE **ArqLi, Registro *UltLido, int *Li, short *OndeLer);
void InserirArea(Registro *Area, Registro *UltLido, int *NRArea);
void EscreveMax(FILE **ArqLEs, Registro R, int *Es);
void EscreveMin(FILE **ArqEi, Registro R, int *Ei);
void RetiraMax(Registro *Area, Registro *R, int *NRArea);
void RetiraMin(Registro *Area, Registro *R, int *NRArea);