#include "s21_tests.h"

void s21_generate_matrix(matrix_t *A) {
  double num = A->rows + A->columns;
  for (int sign = 1, i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns;
         j++, num += sign * (A->rows - A->columns) * (i + j), sign *= -1) {
      A->matrix[i][j] = num;
    }
}

int main() {
  Suite *s21_tests[] = {create_tests(), equals_tests(), arithmetic_tests(),
                        transform_tests(), NULL};

  int failed = 0;
  for (int i = 0; s21_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_tests[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
