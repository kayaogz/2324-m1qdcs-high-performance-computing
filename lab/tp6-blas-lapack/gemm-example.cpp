// Installation: Install openblas-dev in linux, Accelerate framework in Mac to get BLAS and LAPACK functions
// Compilation: g++ -O2 gemm-example.cpp -o gemm-example -fopenmp -lblas
// Execution: ./gemm-example
#include <iostream>
#include <vector>

// Matrix-matrix multiplication, alpha and beta are scalars and op(.) is an optional matrix transposition operator.
// Produit matrice-vecteur, alpha et beta sont des scalaires et op(.) est une transposition matricielle optionnelle.
// C = alpha opA(A) op(B) + beta op(C) (BLAS3)
extern "C" void dgemm_(
  char *transA,
  char *transB,
  int *m,
  int *n,
  int *k,
  double *alpha,
  double *A,
  int *lda,
  double *B,
  int *ldb,
  double *beta,
  double *C,
  int *ldc);

int main()
{
  // Allocate matrices A, B, C of size N x N
  // Allouer les matrices A, B, C de taille N x N
  int N = 8;
  std::vector<double> A(N * N), B(N * N), C(N * N);

  // Initialize A(i, j) = i + j, B(i, j) = 1, C(i, j) = 0
  // Initializer A(i, j) = i + j, B(i, j) = 1, C(i, j) = 0
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      A[i + j * N] = i + j;
      B[i + j * N] = 1.0;
      C[i + j * N] = 0.0;
    }
  }
  char transA = 'N', transB = 'N';
  int m = N, n = N, k = N;
	int lda = N, ldb = N, ldc = N;
  double alpha = 1.0;
  double beta = 0.0;

  // Compute C = 1.0 * A * B + 0.0 * C
  // Calculer C = 1.0 * A * B + 0.0 * C
  dgemm_(&transA, &transB, &m, &n, &k, &alpha, &A[0], &lda, &B[0], &ldb, &beta, &C[0], &ldc);

  // Print matrices
  // Afficher les matrices
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << A[i + j * N] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << B[i + j * N] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << C[i + j * N] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
