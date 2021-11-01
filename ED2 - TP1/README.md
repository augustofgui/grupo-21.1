# Estrutura de Dados 2
## Trabalho Prático 1

```
Acesso Sequencial Indexado - Pedro
Árvore Binária Externa - Paulo
Árvore B - Caio
Árvore B* - Augusto
```

```
gcc geral.c -c
gcc sequencial_indexado.c -c
gcc arvore_externa.c -c
gcc arvore_b.c -c
gcc arvore_bx.c -c
gcc main.c -c
gcc geral.o sequencial_indexado.o arvore_externa.o arvore_b.o arvore_bx.o main.o -o pesquisa
```


* Funções gerais e a estrutura de dados "Registro" estão implementadas em headers/geral.h, basta dar include para utilizá-las.
* O método de pesquisa deve seguir a chamada (e os parâmetros) presentes no arquivo src/main.c
* O método de pesquisa deve retornar 1 se a chave buscada for encontrada e imprimir o registro correspondente a ela.
* O método de pesquisa deve retornar 0 se a chave buscada não for encontrada.
* Não é necessário verificar os argumentos da linha de comando ou criar o arquivo binário, isso já está sendo feito no main.c/geral.c.
