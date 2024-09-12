#include "s21_test.h"

/*  general */
START_TEST(is_greater_or_equal_1) {
  s21_decimal d1 = s21_dec_parse("123.0000000000000000000001");
  s21_decimal d2 = s21_dec_parse("123.");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal d1 = s21_dec_parse("-123.0000000000000000000001");
  s21_decimal d2 = s21_dec_parse("-123");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal d1 = s21_dec_parse("123");
  s21_decimal d2 = s21_dec_parse("123.00000000000000000000");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal d1 = s21_dec_parse("0.000000000000000000123");
  s21_decimal d2 = s21_dec_parse("-12300000000000000000000");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal d1 = s21_dec_parse("12300000000000000000000");
  s21_decimal d2 = s21_dec_parse("0.000000000000000000123");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal d1 = s21_dec_parse("-0.000000000000000000123");
  s21_decimal d2 = s21_dec_parse("-12300000000000000000000");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = S21_DEC_MIN;

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 1);
}
END_TEST

/*  with_NaN */
START_TEST(is_greater_or_equal_8) {
  s21_decimal d1 = s21_dec_parse("123");
  s21_decimal d2 = S21_DEC_NAN;

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal d1 = S21_DEC_NAN;
  s21_decimal d2 = s21_dec_parse("123");

  int ret = s21_is_greater_or_equal(d1, d2);

  ck_assert_int_eq(ret, 0);
}
END_TEST

Suite *s21_test_is_greater_or_equal() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, is_greater_or_equal_1);
  tcase_add_test(case_1, is_greater_or_equal_2);
  tcase_add_test(case_1, is_greater_or_equal_3);
  tcase_add_test(case_1, is_greater_or_equal_4);
  tcase_add_test(case_1, is_greater_or_equal_5);
  tcase_add_test(case_1, is_greater_or_equal_6);
  tcase_add_test(case_1, is_greater_or_equal_7);

  TCase *case_2 = tcase_create(C_RED "with_NaN" C_DEFAULT);
  tcase_add_test(case_2, is_greater_or_equal_8);
  tcase_add_test(case_2, is_greater_or_equal_9);

  Suite *suite = suite_create(C_CYAN "s21_is_greater_or_equal" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}