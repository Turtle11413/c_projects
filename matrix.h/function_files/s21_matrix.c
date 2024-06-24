#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int return_value = OK;

  if (columns > 0 && rows > 0 && result) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double**)calloc(rows, sizeof(double*));
    if (result->matrix) {
      for (int i = 0; i < rows; ++i) {
        result->matrix[i] = (double*)calloc(columns, sizeof(double));
        if (!result->matrix) {
          return_value = INCORRECT_MATRIX;
          break;
        }
      }
    } else {
      return_value = INCORRECT_MATRIX;
    }
  } else {
    return_value = INCORRECT_MATRIX;
  }
  if (return_value == INCORRECT_MATRIX) s21_remove_matrix(result);
  return return_value;
}

void s21_remove_matrix(matrix_t* A) {
  if (A) {
    if (A->matrix) {
      for (int i = 0; i < A->rows; ++i) {
        free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int return_value = FAILURE;
  if (s21_validate_matrix(A) && s21_validate_matrix(B) &&
      s21_check_size_two_matrices(A, B)) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        return_value = (fabs(A->matrix[i][j] - B->matrix[i][j]) < 1e-6);
      }
    }
  }
  return return_value;
}
