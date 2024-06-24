#include "../s21_matrix.h"

int s21_validate_matrix(matrix_t* A) {
  return !(A == NULL || A->matrix == NULL || A->columns < 1 || A->rows < 1);
}

int s21_check_size_two_matrices(matrix_t* A, matrix_t* B) {
  return A->columns == B->columns && A->rows == B->rows;
}
