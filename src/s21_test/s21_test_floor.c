#include "s21_test.h"

/*  general */
START_TEST(floor_1) {
  s21_decimal dec = s21_dec_parse("-123.000");
  s21_decimal expected = s21_dec_parse("-123");

  s21_decimal actual;
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_1\' failed!");
}
END_TEST

START_TEST(floor_2) {
  s21_decimal dec = s21_dec_parse("123.000000000000000000001");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_2\' failed!");
}
END_TEST

START_TEST(floor_3) {
  s21_decimal dec = s21_dec_parse("-123.000000000000000000001");
  s21_decimal expected = s21_dec_parse("-124");

  s21_decimal actual;
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_3\' failed!");
}
END_TEST

START_TEST(floor_4) {
  s21_decimal dec = S21_DEC_MAX_NEG;
  s21_decimal expected = s21_dec_parse("-1");

  s21_decimal actual;
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_4\' failed!");
}
END_TEST

START_TEST(floor_5) {
  s21_decimal dec = S21_DEC_MIN_POS;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_5\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(floor_6) {
  s21_decimal dec = {0};

  int ret = s21_floor(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal dec = S21_DEC_NAN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_floor(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'floor_7\' failed!");
}
END_TEST

Suite *s21_test_floor() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, floor_1);
  tcase_add_test(case_1, floor_2);
  tcase_add_test(case_1, floor_3);
  tcase_add_test(case_1, floor_4);
  tcase_add_test(case_1, floor_5);

  TCase *case_2 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_2, floor_6);
  tcase_add_test(case_2, floor_7);

  Suite *suite = suite_create(C_CYAN "s21_floor" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  return suite;
}