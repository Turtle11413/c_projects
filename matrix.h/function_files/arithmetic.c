#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int return_value = OK;

  if (!s21_validate_matrix(A) || !s21_validate_matrix(B)) {
    return_value = INCORRECT_MATRIX;
  } else if (!s21_check_size_two_matrices(A, B)) {
    return_value = CALCULATION_ERR;
  } else {
    if ((return_value = s21_create_matrix(A->rows, A->columns, result)) == OK) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return return_value;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int return_value = OK;

  if (!s21_validate_matrix(A) || !s21_validate_matrix(B)) {
    return_value = INCORRECT_MATRIX;
  } else if (!s21_check_size_two_matrices(A, B)) {
    return_value = CALCULATION_ERR;
  } else {
    if ((return_value = s21_create_matrix(A->rows, A->columns, result)) == OK) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return return_value;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int return_value = OK;

  if (!s21_validate_matrix(A)) {
    return_value = INCORRECT_MATRIX;
  } else {
    if ((return_value = s21_create_matrix(A->rows, A->columns, result)) == OK) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return return_value;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int return_value = OK;
  if (!s21_validate_matrix(A) || !s21_validate_matrix(B)) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    return_value = CALCULATION_ERR;
  } else {
    if ((return_value = s21_create_matrix(A->rows, B->columns, result)) == OK) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->columns; ++j) {
          for (int m = 0; m < B->rows; ++m) {
            result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
          }
        }
      }
    }
  }
  return return_value;
}
