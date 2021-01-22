#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numLin (char *nomeArq) {
    FILE *arq;
    char c;
    int lin = 0;

    arq = fopen (nomeArq, "r");

    if (arq == NULL) {
    	printf ("Erro ao abrir o arquivo!");
    	return 0;
    }

    while ((c = fgetc(arq)) != EOF) {
        if (c == '\n') {
            lin++;
        }
    }

    fclose(arq);

    if(c != '\n') {
        lin++;
    }

    return lin;
}

int numCol (char *nomeArq) {
    FILE *arq;
    char c;
    int col = 0;

    arq = fopen(nomeArq, "r");

    if (arq == NULL) {
    	printf ("Erro ao abrir o arquivo!");
    	return 0;
    }

    while (((c = fgetc(arq)) != EOF) && (c != '\n')) {
        if (c != ' ') {
            col++;
        }
    }

    fclose(arq);

    if(c != '\n') {
        col++;
    }

    return col;
}

void preencheMatrizArquivo (char *nomeArq, int lin, int col, float m[lin][col]) {

	FILE *arq;
	arq = fopen(nomeArq, "r");
	int i, j;
	float aux;
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {

			if ((i == 0) && (j != col-1)){
				fscanf (arq, "%f", &aux);
				m[i][j] = aux * (-1.0);
			}
			
			else {
				fscanf (arq, "%f", &aux);
				m[i][j] = aux;
			}
			printf ("%f\n", m[i][j]);
		}
	}
	fclose(arq);
}

int calcColTableau (int lin, int col) {
	return lin + col;
}

void imprimeMatriz (int lin, int col, float m[lin][col]) {
	int i, j;
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
}

void preencheMatrizZero (int lin, int col, float m[lin][col]) {
	int i, j;
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {
			m[i][j] = 0.0;
		}
	}
}

void preencheTableauInicial (char *nomeArq, int lin, int col, float m[lin][col], int linOrig, int colOrig, float mOrig[linOrig][colOrig]) {

	FILE *arq;
	int i = 0, j = 0;
	float aux;
	char c;

	arq = fopen(nomeArq, "r");
	
    if (arq == NULL) {
    	printf ("Erro ao abrir o arquivo!");
    }

    preencheMatrizZero (lin, col, m);
    imprimeMatriz (lin, col, m);
	
	for (i = 0; i < lin; i++) {
		j = 0;
		if (i == 0) {
			m[i][j] = 1.0;
		}

		else {
			m[i][j] = 0.0;
		}
		printf ("%f\n", m[i][j]);
	}

	imprimeMatriz (lin, col, m);

	for (i = 0; i < linOrig; i++) {
		for (j = 0; j < colOrig - 1; j++) {
			m[i][j+1] = mOrig[i][j];
		}
	}

	for (i = 0; i < linOrig; i++) {
		for (j = 0; j < colOrig; j++) {
			m[i][col-1] = mOrig[i][j];
		}
	}

	int cont = colOrig;
	for (i = 1; i < lin; i++) {
		for (j = colOrig; j < col - 1; j++) {
			if (j == cont) {
				m[i][j] = 1.0;
			}	
		}
		cont++;
	}

	imprimeMatriz (lin, col, m);

	fclose (arq);
}

int verificaNegativoZ (int lin, int col, float m[lin][col]) {
	int i, j;
	float aux;
	for (i = 0; i <= 0; i++) {
		for (j = 1; j < col - 1; j++) {
			aux = m[i][j];
			if (aux < 0) {
				return 1;
			}

			else {
				return 0;
			}
		}
	}
}

int verificaMenorNegativo (int lin, int col, float m[lin][col]) {
	int i, j, colSelecionada;
	float aux = 0, maiorNeg = 0;

	for (i = 0; i <= 0; i++) {
		for (j = 1; j < col - 1; j++) {
			aux = m[i][j];
			if (abs(aux) > maiorNeg) {
				maiorNeg = abs(aux);
				colSelecionada = j;
			}
		}
	}

	return colSelecionada;
}

int vericaLinhaQueSai (int lin, int col, float m[lin][col], int colSelecionada) {
	int i, j, linhaSai;
	float aux[lin-1][1], aux2[lin-1][1], divi[lin-1][1], aux3 = 0.0, menorPos = 0.0;
	preencheMatrizZero (lin-1, 1, aux);
	preencheMatrizZero (lin-1, 1, aux2);
	preencheMatrizZero (lin-1, 1, divi);

	for (i = 0; i < lin-1; i++) {
		for (j = colSelecionada; j <= colSelecionada; j++) {
			aux[i][1] = m[i+1][j];
			printf("%f\n", aux[i][1]);
		}
	}

	imprimeMatriz (lin, 1, aux);
	printf("-------\n");

	for (i = 0; i < lin-1; i++) {
		for (j = col-1; j <= col-1; j++) {
			aux2[i][1] = m[i+1][j];
			printf("%f\n", aux2[i][1]);
		}
	}

	for (i = 0; i < lin-1; i++) {
		for (j = 1; j <= 1; j++) {
			if (aux[i][j] != 0) {
				divi[i][1] = aux2[i][j] / aux[i][j];
			}

			else {
				divi[i][j] = 0.0;
			}
			printf("%f\n", divi[i][1]);
		}
	}

	for (i = 0; i < lin-1; i++) {
		for (j = 1; j <=1; j++) {
			aux3 = m[i][j];
			menorPos = m[i][j];
			if (aux3 > menorPos) {
				menorPos = aux3;
				linhaSai = i;
			}
		}
	}

	return linhaSai+1;

	imprimeMatriz (lin, 1, aux2);
}

float encontraPivo (int colEntra, int linhaSai, int lin, int col, float m[lin][col]) {
	return m[linhaSai][colEntra];
}

void novaLinhaPivo (int linhaSai, float pivo, int lin, int col, float m[lin][col]) {
	int i, j;
	for (i = linhaSai; i <= linhaSai; i++) {
		for (j = 0; j < col; j++) {
			m[i][j] = m[i][j] / pivo;
		}
	}
}

float pivoColuna (int colunaEntra, int linAtual, int lin, int col, float m[lin][col]) {
	return m[linAtual][colunaEntra];
}

void novasLinhas (int linhaSai, int colEntra, int lin, int col, float m[lin][col]) {
	int i, j;
	float aux[1][col], pivo, aux2;
	preencheMatrizZero (1, col, aux);

	for (j = 0; j < col; j++) {
		aux[1][j] = m[linhaSai][j];
	}

	for (i = 0; i < linhaSai; i++) { //muda linhas antes da linha que sai
		pivo = pivoColuna (colEntra, i, lin, col, m);
		printf("%f", pivo);
		for (j = 0; j < col; j++) {
			aux2 = m[linhaSai][j] * pivo;
			m[i][j] = m[i][j] + aux2;
		}
	}
	
	imprimeMatriz (lin, col, m);
}