/*
 * File:   main.cpp
 * Author: Zosia
 *
 * Created on October 18, 2013, 11:46 AM
 */

#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

double* createMatrix(int M, int N = 1);
void destroyMatrix(double* matrix);
void fillMatrix(double* matrix, int M, int N = 1);
double* multiple(double* A, double* B, int M, int N);
void multiple(double* A, double* B, int M, int N, double* out);

void usage();

int M, N;

/*
 *
 */
int main(int argc, char** argv) {

    if (argc != 3) {
        usage();
    }

    M = (int) atoi(argv[1]);
    N = (int) atoi(argv[2]);

    double* A = createMatrix(M, N);
    fillMatrix(A, M, N);
    double* B = createMatrix(N, M);
    fillMatrix(B, N, M);
    double* out = createMatrix(M, M);

    multiple(A, B, M, N, out);

    destroyMatrix(A);
    destroyMatrix(B);
    destroyMatrix(out);


    return 0;
}

double* createMatrix(int M, int N) {
    double* matrix = new double[M * N];
    return matrix;
}

void destroyMatrix(double* matrix) {
    delete[] matrix;
}

void fillMatrix(double* matrix, int M, int N) {
    int size = M*N;
    for (int i = 0; i < size; i++) {
        matrix[i] = rand();
    }
}

double* multiple(double* A, double* B, int M, int N) {
    double* out = createMatrix(M, M);
    multiple(A, B, M, N, out);
    return out;
}

void multiple(double* A, double* B, int M, int N, double* out) {

    double time = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < M * M; i++) {
        int m = i / N;
        out[i] = 0;
        for (int n = 0; n < N; n++) {
            out[i] += A[m * N + n] * B[n * M + m];
        }
    }
    time = omp_get_wtime() - time;
    cout << time;
}

void usage() {
    cout << "Usage: main <M> <N>" << endl
            << "A[M][N] x B[N][M]" << endl
            << "where A - multipland" << endl
            << "where B - multiplier" << endl
            << "matrix[rows][cols]" << endl;
    exit(64);
}
