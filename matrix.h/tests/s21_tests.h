#ifndef S21_MATRIX_TESTS_H
#define S21_MATRIX_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *create_tests();
Suite *equals_tests();
Suite *arithmetic_tests();
Suite *transform_tests();
////////////////////////
void s21_generate_matrix(matrix_t *A);

#endif  // S21_MATRIX_TESTS_H
