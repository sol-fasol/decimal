#include "s21_test.h"

/*  general */
START_TEST(truncate_1) {
  s21_decimal dec = s21_dec_parse("-12345678901234567890");
  s21_decimal expected = s21_dec_parse("-12345678901234567890");

  s21_decimal actual;
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_1\' failed!");
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal dec = s21_dec_parse("123.000000000000000000001");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_2\' failed!");
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal dec = s21_dec_parse("-123.5000000000");
  s21_decimal expected = s21_dec_parse("-123");

  s21_decimal actual;
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_3\' failed!");
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal dec = s21_dec_parse("1234.9999999999999999999999");
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual;
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_4\' failed!");
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal dec = S21_DEC_MAX_NEG;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_5\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(truncate_6) {
  s21_decimal dec = {0};

  int ret = s21_truncate(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal dec = S21_DEC_NAN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_truncate(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'truncate_7\' failed!");
}
END_TEST

Suite *s21_test_truncate() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, truncate_1);
  tcase_add_test(case_1, truncate_2);
  tcase_add_test(case_1, truncate_3);
  tcase_add_test(case_1, truncate_4);
  tcase_add_test(case_1, truncate_5);

  TCase *case_2 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_2, truncate_6);
  tcase_add_test(case_2, truncate_7);

  Suite *suite = suite_create(C_CYAN "s21_truncate" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}