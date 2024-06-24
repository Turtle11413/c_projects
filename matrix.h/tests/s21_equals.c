#include "s21_tests.h"

START_TEST(equals_test_1) {
  matrix_t result = {}, m = {};
  s21_create_matrix(1, 1, &result);
  result.matrix[0][0] = 2;
  s21_create_matrix(1, 1, &m);
  s21_generate_matrix(&m);
  ck_assert_int_eq(s21_eq_matrix(&m, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(equals_test_2) {
  matrix_t result = {}, m = {};
  s21_create_matrix(2, 3, &result);
  result.matrix[0][0] = 5;
  result.matrix[0][1] = 4;
  result.matrix[0][2] = 6;
  result.matrix[1][0] = 3;
  result.matrix[1][1] = 5;
  result.matrix[1][2] = 2;
  s21_create_matrix(2, 3, &m);
  s21_generate_matrix(&m);
  ck_assert_int_eq(s21_eq_matrix(&m, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(equals_test_3) {
  matrix_t result = {}, m = {};
  s21_create_matrix(3, 2, &result);
  result.matrix[0][0] = 5;
  result.matrix[0][1] = 6;
  result.matrix[1][0] = 4;
  result.matrix[1][1] = 6;
  result.matrix[2][0] = 3;
  result.matrix[2][1] = 6;
  s21_create_matrix(3, 2, &m);
  s21_generate_matrix(&m);
  ck_assert_int_eq(s21_eq_matrix(&m, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(equals_test_4) {
  matrix_t result = {}, m = {};
  s21_create_matrix(2, 1, &result);
  s21_create_matrix(2, 2, &m);
  s21_generate_matrix(&m);
  ck_assert_int_eq(s21_eq_matrix(&m, &result), FAILURE);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

Suite *equals_tests() {
  Suite *suite = suite_create("---EQUALS---");
  TCase *tcase = tcase_create("matrix_tc");

  tcase_add_test(tcase, equals_test_1);
  tcase_add_test(tcase, equals_test_2);
  tcase_add_test(tcase, equals_test_3);
  tcase_add_test(tcase, equals_test_4);

  suite_add_tcase(suite, tcase);
  return suite;
}