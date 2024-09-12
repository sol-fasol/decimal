#include "s21_test.h"

/*  general */
START_TEST(from_decimal_to_float_1) {
  s21_decimal dec = s21_dec_parse("123.00000");
  float expected = 123.f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_1\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal dec = s21_dec_parse("12345686543654.6455453765");
  float expected = 12345686543654.6455453765f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_2\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal dec = s21_dec_parse("-1000000000000000");
  float expected = -1000000000000000.f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_3\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal dec = s21_dec_parse("12345678909876543212345678");
  float expected = 12345678909876543212345678.f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_4\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal dec = s21_dec_parse("0.00001234567890123456");
  float expected = 0.00001234567890123456f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_5\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_6) {
  s21_decimal dec = s21_dec_parse("12345678");
  float expected = 12345678.f;

  float actual = 0.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_6\' failed!");
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  s21_decimal dec = s21_dec_parse("0");
  float expected = 0.f;

  float actual = 123.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_7\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(from_decimal_to_float_8) {
  s21_decimal dec = s21_dec_parse("0");

  int ret = s21_from_decimal_to_float(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(from_decimal_to_float_9) {
  s21_decimal dec = S21_DEC_NAN;
  float expected = 123.f;

  float actual = 123.f;
  int ret = s21_from_decimal_to_float(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(expected == actual, "Test \'from_decimal_to_float_9\' failed!");
}
END_TEST

Suite *s21_test_from_decimal_to_float() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, from_decimal_to_float_1);
  tcase_add_test(case_1, from_decimal_to_float_2);
  tcase_add_test(case_1, from_decimal_to_float_3);
  tcase_add_test(case_1, from_decimal_to_float_4);
  tcase_add_test(case_1, from_decimal_to_float_5);
  tcase_add_test(case_1, from_decimal_to_float_6);
  tcase_add_test(case_1, from_decimal_to_float_7);

  TCase *case_2 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_2, from_decimal_to_float_8);
  tcase_add_test(case_2, from_decimal_to_float_9);

  Suite *suite = suite_create(C_CYAN "s21_from_decimal_to_float" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  return suite;
}