#include "s21_test.h"

/*  general */
START_TEST(from_decimal_to_int_1) {
  s21_decimal dec = s21_dec_parse("123.456");
  int expected = 123;

  int actual = 0;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal dec = s21_dec_parse("2147483647.9999999999999999");
  int expected = 2147483647;

  int actual = 0;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal dec = s21_dec_parse("-1.999999999999999999999");
  int expected = -1;

  int actual = 0;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal dec = s21_dec_parse("-2147483648.00000000001");
  int expected = -2147483648;

  int actual = 0;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal dec = s21_dec_parse("-0.5");
  int expected = 0;

  int actual = 123;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(expected, actual);
}
END_TEST

/*  with_overflow */
START_TEST(from_decimal_to_int_6) {
  s21_decimal dec = s21_dec_parse("2147483648");
  int expected = -123;

  int actual = -123;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(expected, actual);
}
END_TEST

START_TEST(from_decimal_to_int_7) {
  s21_decimal dec = s21_dec_parse("-100000000000000");
  int expected = 123;

  int actual = 123;
  int ret = s21_from_decimal_to_int(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(expected, actual);
}
END_TEST

/*  with_NULL */
START_TEST(from_decimal_to_int_8) {
  s21_decimal dec = {0};

  int ret = s21_from_decimal_to_int(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *s21_test_from_decimal_to_int() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, from_decimal_to_int_1);
  tcase_add_test(case_1, from_decimal_to_int_2);
  tcase_add_test(case_1, from_decimal_to_int_3);
  tcase_add_test(case_1, from_decimal_to_int_4);
  tcase_add_test(case_1, from_decimal_to_int_5);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, from_decimal_to_int_6);
  tcase_add_test(case_2, from_decimal_to_int_7);

  TCase *case_3 = tcase_create(C_RED "with_NULL" C_DEFAULT);
  tcase_add_test(case_3, from_decimal_to_int_8);

  Suite *suite = suite_create(C_CYAN "s21_from_decimal_to_int" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  suite_add_tcase(suite, case_3);
  return suite;
}