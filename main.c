#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void liberaMatriz(double **matriz, int n);
void eliminacaoGauss(double **matriz, double *vetorB, int n);
void substituicaoSucessiva(double **matriz, double *vetorB, double *vetorX, int n);

int main(int argc, char *argv[]) {

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int dimensao;
    if (fscanf(fptr, "%i", &dimensao) != 1) {
        perror("Erro ao ler a dimensão");
        fclose(fptr);
        return 1;
    }

    double **matrizA = (double **)malloc(dimensao * sizeof(double *));
    if (matrizA == NULL) {
        perror("Erro ao alocar memória para linhas da matriz");
        fclose(fptr);
        return 1;
    }

    for (int i = 0; i < dimensao; i++) {
        matrizA[i] = (double *)malloc(dimensao * sizeof(double));
        if (matrizA[i] == NULL) {
            perror("Erro ao alocar memória para colunas da matriz");
            fclose(fptr);
            liberaMatriz(matrizA, i);
            return 1;
        }
    }

    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (fscanf(fptr, "%lf", &matrizA[i][j]) != 1) {
                perror("Erro ao ler os valores da matriz");
                fclose(fptr);
                liberaMatriz(matrizA, i);
                return 1;
            }
        }
    }

    double *vetorB = (double *)malloc(dimensao * sizeof(double));
    if (vetorB == NULL) {
        perror("Erro ao alocar memória para o vetor de resultados");
        liberaMatriz(matrizA, dimensao);
        fclose(fptr);
        return 1;
    }

    for (int i = 0; i < dimensao; i++) {
        if (fscanf(fptr, "%lf", &vetorB[i]) != 1) {
            perror("Erro ao ler os valores do vetor de resultados");
            liberaMatriz(matrizA, dimensao);
            free(vetorB);
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);

    double *vetorX = (double *)malloc(dimensao * sizeof(double));
    if (vetorX == NULL) {
        perror("Erro ao alocar memória para o vetor de variáveis");
        liberaMatriz(matrizA, dimensao);
        free(vetorB);
        return 1;
    }

    // Exibir a matriz e o vetor lidos
    printf("Matriz lida do arquivo:\n");
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            printf("%lf ", matrizA[i][j]);
        }
        printf("\n");
    }

    printf("Vetor de resultados:\n");
    for (int i = 0; i < dimensao; i++) {
        printf("%lf\n", vetorB[i]);
    }

    eliminacaoGauss(matrizA, vetorB, dimensao);
    //substituicaoSucessiva(matrizA, vetorB, vetorX, dimensao);

    printf("Vetor de variaveis:\n");
    for (int i = 0; i < dimensao; i++) {
        printf("%lf\n", vetorX[i]);
    }

    liberaMatriz(matrizA, dimensao);
    free(vetorB);
    free(vetorX);
    return 0;
}

void liberaMatriz(double **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void eliminacaoGauss(double **matriz, double *vetorB, int n) {
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );

    FILE *log = fopen("log.txt", "a");
    if (log == NULL) {
        perror("Erro ao abrir o arquivo de log");
    }

    fprintf(log, "Matriz:\t--%s\n", asctime(info));

    //iteração sobre as etapas (k)
    for (int k = 0; k < n-1; k++) {

        fprintf(log, "Etapa %d:\n", k);
        fprintf(log, "Pivo: a[%d][%d]\n", k, k);

        //iteração sobre as linhas abaixo (k+1) da linha do pivô (akk)
        for (int i = k + 1; i < n; i++) {

            //cálculo do multiplicador de cada linha
            double m = matriz[i][k] / matriz[k][k];

            fprintf(log, "m[%d][%d] = %lf / %lf = %lf\n", i, k, matriz[i][k], matriz[k][k], m);
            fprintf(log, "L[%d] <- L[%d] - m[%d][%d] * L[%d]\n\n", i, i, i, k, k);
            //adianta que o item será zerado evitando iterações e cálculos desnecessários
            matriz[i][k] = 0;

            //operação elementar sobre os elementos j da linha i utilizando a linha k
            for (int j = k + 1; j < n; j++)
                matriz[i][j] = matriz[i][j] - m * matriz[k][j];

            //operação elementar sobre o vetor b
            vetorB[i] = vetorB[i] - m * vetorB[k];

            fprintf(log, "Matriz ao fim da etapa %d:\n", k);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(log, "%lf ", matriz[i][j]);
                }
                fprintf(log, "\n\n");
            }

            fprintf(log, "Vetor b:\n");
            for (int i = 0; i < n; i++) {
                fprintf(log, "%lf ", vetorB[i]);
            }
            fprintf(log, "\n\n----------------------------------------------------\n\n");

        }
    }
    fclose(log);
}

void substituicaoSucessiva(double **matriz, double *vetorB, double *vetorX, int n) {

}