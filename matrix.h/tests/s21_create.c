#include "s21_tests.h"

START_TEST(create_test_1) {
  matrix_t m = {};
  int res = s21_create_matrix(1, 1, &m);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_test_2) {
  matrix_t m = {};
  int res = s21_create_matrix(13, 251, &m);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_test_3) {
  matrix_t m = {};
  int res = s21_create_matrix(2, 2, &m);
  ck_assert_int_eq(res, OK);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[1][0] = 3;
  m.matrix[1][1] = 4;
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_test_4) {
  matrix_t m = {};
  int res = s21_create_matrix(-2, 3, &m);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_test_5) {
  int res = s21_create_matrix(1, 1, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

Suite *create_tests() {
  Suite *suite = suite_create("---CREATE_REMOVE---");
  TCase *tcase = tcase_create("matrix_tc");

  tcase_add_test(tcase, create_test_1);
  tcase_add_test(tcase, create_test_2);
  tcase_add_test(tcase, create_test_3);
  tcase_add_test(tcase, create_test_4);
  tcase_add_test(tcase, create_test_5);

  suite_add_tcase(suite, tcase);
  return suite;
}