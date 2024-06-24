#include "s21_tests.h"

START_TEST(sum_test_1) {
  matrix_t result = {}, m1 = {}, m2 = {}, m_res = {};
  s21_create_matrix(1, 1, &m1);
  s21_create_matrix(1, 1, &m2);
  s21_generate_matrix(&m1);
  s21_generate_matrix(&m2);
  s21_create_matrix(1, 1, &result);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_res), OK);
  ck_assert_int_eq(s21_eq_matrix(&m_res, &result), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m_res);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_2) {
  matrix_t m1 = {}, m2 = {}, m_res = {};
  s21_create_matrix(1, 3, &m1);
  s21_create_matrix(2, 3, &m2);
  s21_generate_matrix(&m1);
  s21_generate_matrix(&m2);
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_res), CALCULATION_ERR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(sub_test_1) {
  matrix_t result = {}, m1 = {}, m2 = {}, m_res = {};
  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(3, 3, &m2);
  s21_generate_matrix(&m1);
  s21_generate_matrix(&m2);
  s21_create_matrix(3, 3, &result);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_res), OK);
  ck_assert_int_eq(s21_eq_matrix(&m_res, &result), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m_res);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_2) {
  matrix_t m1 = {}, m2 = {}, m_res = {};
  s21_create_matrix(4, 3, &m1);
  s21_create_matrix(2, 3, &m2);
  s21_generate_matrix(&m1);
  s21_generate_matrix(&m2);
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_res), CALCULATION_ERR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(mult_number_test_1) {
  matrix_t result = {}, m = {}, m_res = {};
  s21_create_matrix(3, 4, &m);
  s21_generate_matrix(&m);
  s21_create_matrix(3, 4, &result);
  double number = 12.642;
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      result.matrix[i][j] = m.matrix[i][j] * number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&m, number, &m_res), OK);
  ck_assert_int_eq(s21_eq_matrix(&m_res, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&m_res);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_test_1) {
  matrix_t result = {}, m1 = {}, m2 = {}, m_res = {};
  s21_create_matrix(2, 3, &m1);
  s21_create_matrix(3, 2, &m2);
  s21_generate_matrix(&m1);
  s21_generate_matrix(&m2);
  s21_create_matrix(2, 2, &result);
  result.matrix[0][0] = 59;
  result.matrix[0][1] = 90;
  result.matrix[1][0] = 41;
  result.matrix[1][1] = 60;
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &m_res), OK);
  ck_assert_int_eq(s21_eq_matrix(&m_res, &result), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m_res);
  s21_remove_matrix(&result);
}
END_TEST

Suite *arithmetic_tests() {
  Suite *suite = suite_create("---ARITHMETIC---");
  TCase *tcase = tcase_create("matrix_tc");

  tcase_add_test(tcase, sum_test_1);
  tcase_add_test(tcase, sum_test_2);
  tcase_add_test(tcase, sub_test_1);
  tcase_add_test(tcase, sub_test_2);
  tcase_add_test(tcase, mult_number_test_1);
  tcase_add_test(tcase, mult_test_1);

  suite_add_tcase(suite, tcase);
  return suite;
}
