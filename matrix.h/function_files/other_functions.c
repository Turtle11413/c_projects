#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_value = OK;

  if (!s21_validate_matrix(A)) {
    return_value = INCORRECT_MATRIX;
  } else {
    if ((return_value = s21_create_matrix(A->columns, A->rows, result)) == OK) {
      for (int i = 0; i < A->columns; ++i) {
        for (int j = 0; j < A->rows; ++j) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return return_value;
}

int s21_determinant(matrix_t *A, double *result) {
  int return_value = OK;
  if (!s21_validate_matrix(A)) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    return_value = CALCULATION_ERR;
  } else {
    *result = s21_get_me_det(A);
  }
  return return_value;
}

double s21_get_me_det(matrix_t *A) {
  double result = 0;
  if (A->rows == 1)
    result = A->matrix[0][0];
  else {
    matrix_t minor = {};
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    for (int i = 0, sign = 1; i < A->rows; i++, sign *= -1) {
      s21_get_minor(A, &minor, 0, i);
      result += sign * A->matrix[0][i] * s21_get_me_det(&minor);
    }
    s21_remove_matrix(&minor);
  }

  return result;
}

void s21_get_minor(matrix_t *A, matrix_t *minor, int cur_row, int cur_col) {
  for (int i = 0, x = 0; i < A->rows; i++) {
    for (int j = 0, y = 0; j < A->columns; j++) {
      if (i != cur_row && j != cur_col) {
        minor->matrix[x][y++] = A->matrix[i][j];
        if (y == minor->rows) {
          y = 0;
          x++;
        }
      }
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_value = OK;
  if (!s21_validate_matrix(A))
    return_value = INCORRECT_MATRIX;
  else if (A->columns != A->rows)
    return_value = CALCULATION_ERR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows != 1) {
      matrix_t minor = {};
      s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_get_minor(A, &minor, i, j);
          int sign = ((i + j) % 2 == 0) ? 1 : -1;
          result->matrix[i][j] = sign * s21_get_me_det(&minor);
        }
      }
      s21_remove_matrix(&minor);
    } else {
      result->matrix[0][0] = A->matrix[0][0];
    }
  }

  return return_value;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_value = OK;
  if (!s21_validate_matrix(A)) {
    return_value = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    return_value = CALCULATION_ERR;
  } else {
    double det = s21_get_me_det(A);
    if (fabs(det) < 1e-6) {
      return_value = CALCULATION_ERR;
    } else {
      matrix_t comps = {}, comps_transpose = {};

      s21_calc_complements(A, &comps);
      s21_transpose(&comps, &comps_transpose);
      s21_create_matrix(A->rows, A->rows, result);

      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->rows; j++)
          result->matrix[i][j] = comps_transpose.matrix[i][j] / det;

      s21_remove_matrix(&comps_transpose);
      s21_remove_matrix(&comps);
    }
  }

  return return_value;
}
