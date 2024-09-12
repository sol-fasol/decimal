#include "s21_test.h"

/*  general */
START_TEST(negate_1) {
  s21_decimal dec = s21_dec_parse("-123");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = {0};
  int ret = s21_negate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'negate_1\' failed!");
}
END_TEST

START_TEST(negate_2) {
  s21_decimal dec = s21_dec_parse("1654365465436543654623.000");
  s21_decimal expected = s21_dec_parse("-1654365465436543654623");

  s21_decimal actual = {0};
  int ret = s21_negate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'negate_2\' failed!");
}
END_TEST

START_TEST(negate_3) {
  s21_decimal dec = S21_DEC_MAX;
  s21_decimal expected = S21_DEC_MIN;

  s21_decimal actual = {0};
  int ret = s21_negate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'negate_3\' failed!");
}
END_TEST

START_TEST(negate_4) {
  s21_decimal dec = {0};
  s21_decimal expected = {0};

  s21_decimal actual = {0};
  int ret = s21_negate(dec, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'negate_4\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(negate_5) {
  s21_decimal dec = {0};

  int ret = s21_negate(dec, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(negate_6) {
  s21_decimal dec = S21_DEC_NAN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_negate(dec, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'negate_6\' failed!");
}
END_TEST

Suite *s21_test_negate() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, negate_1);
  tcase_add_test(case_1, negate_2);
  tcase_add_test(case_1, negate_3);
  tcase_add_test(case_1, negate_4);

  TCase *case_2 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_2, negate_5);
  tcase_add_test(case_2, negate_6);

  Suite *suite = suite_create(C_CYAN "\n s21_negate" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}