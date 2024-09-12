#include "s21_test.h"

/*  general */
START_TEST(round_1) {
  s21_decimal dec = s21_dec_parse("-123");
  s21_decimal expected = s21_dec_parse("-123");

  s21_decimal actual;
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_1\' failed!");
}
END_TEST

START_TEST(round_2) {
  s21_decimal dec = s21_dec_parse("123.000000000000000000001");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_2\' failed!");
}
END_TEST

START_TEST(round_3) {
  s21_decimal dec = s21_dec_parse("-123.5000000000");
  s21_decimal expected = s21_dec_parse("-124");

  s21_decimal actual;
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_3\' failed!");
}
END_TEST

START_TEST(round_4) {
  s21_decimal dec = s21_dec_parse("1234.50000000000000000001");
  s21_decimal expected = s21_dec_parse("1235");

  s21_decimal actual;
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_4\' failed!");
}
END_TEST

START_TEST(round_5) {
  s21_decimal dec = s21_dec_parse("1234.50000000000000000000");
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual;
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_5\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(round_6) {
  s21_decimal dec = {0};

  int ret = s21_round(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(round_7) {
  s21_decimal dec = S21_DEC_NAN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_round(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'round_7\' failed!");
}
END_TEST

Suite *s21_test_round() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, round_1);
  tcase_add_test(case_1, round_2);
  tcase_add_test(case_1, round_3);
  tcase_add_test(case_1, round_4);
  tcase_add_test(case_1, round_5);

  TCase *case_2 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_2, round_6);
  tcase_add_test(case_2, round_7);

  Suite *suite = suite_create(C_CYAN "s21_round" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}