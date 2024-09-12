#include "s21_test.h"

/*  general */
START_TEST(add_1) {
  s21_decimal d1 = s21_dec_parse("000000123");
  s21_decimal d2 = s21_dec_parse("000000321");
  s21_decimal expected = s21_dec_parse("444");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_1\' failed!");
}
END_TEST

START_TEST(add_2) {
  s21_decimal d1 = s21_dec_parse("-00000033333333333333333333.000");
  s21_decimal d2 = s21_dec_parse("-00000033333333333333333333");
  s21_decimal expected = s21_dec_parse("-66666666666666666666");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_2\' failed!");
}
END_TEST

START_TEST(add_3) {
  s21_decimal d1 = s21_dec_parse("00000033333333333333333333");
  s21_decimal d2 = s21_dec_parse("00000000000000000000000000.0333333335");
  s21_decimal expected = s21_dec_parse("33333333333333333333.033333334");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_3\' failed!");
}
END_TEST

START_TEST(add_4) {
  s21_decimal d1 = s21_dec_parse("00000000000000000000000000.0222222225");
  s21_decimal d2 = s21_dec_parse("00000022222222222222222222");
  s21_decimal expected = s21_dec_parse("22222222222222222222.022222222");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_4\' failed!");
}
END_TEST

START_TEST(add_5) {
  s21_decimal d1 = s21_dec_parse("0000000792281625142643375935.43950335");
  s21_decimal d2 = s21_dec_parse("0000000792281625142643375935.43950320");
  s21_decimal expected = s21_dec_parse("1584563250285286751870.8790066");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_5\' failed!");
}
END_TEST

START_TEST(add_6) {
  s21_decimal d1 = s21_dec_parse("000000792281625142643375935.43950335");
  s21_decimal d2 = s21_dec_parse("000000079228162514264337593.543950335");
  s21_decimal expected = s21_dec_parse("871509787656907713528.9834537");

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_6\' failed!");
}
END_TEST

START_TEST(add_7) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = s21_dec_parse("-0.4");
  s21_decimal expected = S21_DEC_MAX;

  s21_decimal actual;
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_7\' failed!");
}
END_TEST

/*  with_overflow */
START_TEST(add_8) {
  s21_decimal d1 = s21_dec_parse("-0.5");
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 2);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_8\' failed!");
}
END_TEST

START_TEST(add_9) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = S21_DEC_MAX;
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual = s21_dec_parse("1234");
  int ret = s21_add(d1, d2, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'add_9\' failed!");
}
END_TEST

Suite *s21_test_add() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, add_1);
  tcase_add_test(case_1, add_2);
  tcase_add_test(case_1, add_3);
  tcase_add_test(case_1, add_4);
  tcase_add_test(case_1, add_5);
  tcase_add_test(case_1, add_6);
  tcase_add_test(case_1, add_7);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, add_8);
  tcase_add_test(case_2, add_9);

  Suite *suite = suite_create(C_CYAN "s21_add" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}