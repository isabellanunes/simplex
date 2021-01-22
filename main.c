#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"

int main () {

	char endereco[] = "desafio1.txt";
   
    int linArq = numLin (endereco);
    int colArq = numCol (endereco);

    float matrizArquivo[linArq][colArq];

    preencheMatrizArquivo (endereco, linArq, colArq, matrizArquivo);

    imprimeMatriz (linArq, colArq, matrizArquivo);

    int linTableau = linArq;
    int colTableau = calcColTableau (linArq, colArq);
    
    float tableau[linTableau][colTableau];

    preencheTableauInicial (endereco, linTableau, colTableau, tableau, linArq, colArq, matrizArquivo);

    imprimeMatriz (linTableau, colTableau, tableau);

    int aux;

    int colEntra = verificaMenorNegativo (linTableau, colTableau, tableau);

    int linhaSai = vericaLinhaQueSai (linTableau, colTableau, tableau, colEntra);
    
    printf ("%d\n", linhaSai);

    float pivo = encontraPivo (colEntra, linhaSai, linTableau, colTableau, tableau);
    printf ("%f\n\n", pivo);

    novaLinhaPivo (linhaSai, pivo, linTableau, colTableau, tableau);

    imprimeMatriz (linTableau, colTableau, tableau);
    printf ("---------------------\n");

    novasLinhas (linhaSai, colEntra, linTableau, colTableau, tableau);

    imprimeMatriz (linTableau, colTableau, tableau);
    
 	return 0;
}