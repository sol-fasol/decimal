#ifndef S21_TEST_H

#define S21_TEST_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/s21_arithmetic.h"
#include "../s21_decimal.h"

#define C_DEFAULT "\033[0m"
#define C_RED "\033[31m"
#define C_CYAN "\033[36m"

#define S21_DEC_NAN \
  {                 \
    { 0, 0, 0, 1 }  \
  }
#define S21_DEC_MAX                                          \
  {                                                          \
    { (int)0xffffffff, (int)0xffffffff, (int)0xffffffff, 0 } \
  }
#define S21_DEC_MIN                                                        \
  {                                                                        \
    { (int)0xffffffff, (int)0xffffffff, (int)0xffffffff, (int)0x80000000 } \
  }
#define S21_DEC_MAX_NEG          \
  {                              \
    { 1, 0, 0, (int)0x801C0000 } \
  }
#define S21_DEC_MIN_POS          \
  {                              \
    { 1, 0, 0, (int)0x001C0000 } \
  }

Suite *s21_test_add();
Suite *s21_test_sub();
Suite *s21_test_mul();
Suite *s21_test_div();

Suite *s21_test_is_less();
Suite *s21_test_is_less_or_equal();
Suite *s21_test_is_greater();
Suite *s21_test_is_greater_or_equal();
Suite *s21_test_is_equal();
Suite *s21_test_is_not_equal();

Suite *s21_test_from_int_to_decimal();
Suite *s21_test_from_float_to_decimal();
Suite *s21_test_from_decimal_to_int();
Suite *s21_test_from_decimal_to_float();

Suite *s21_test_floor();
Suite *s21_test_round();
Suite *s21_test_truncate();
Suite *s21_test_negate();

s21_decimal s21_dec_parse(char *str);
int s21_dec_eq(s21_decimal d1, s21_decimal d2);

#endif