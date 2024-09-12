#include "s21_test.h"

/*  general */
START_TEST(from_int_to_decimal_1) {
  int nbr = 123;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_from_int_to_decimal(nbr, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_int_to_decimal_1\' failed!");
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  int nbr = 2147483647;
  s21_decimal expected = s21_dec_parse("2147483647");

  s21_decimal actual;
  int ret = s21_from_int_to_decimal(nbr, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_int_to_decimal_2\' failed!");
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  int nbr = -1;
  s21_decimal expected = s21_dec_parse("-1");

  s21_decimal actual;
  int ret = s21_from_int_to_decimal(nbr, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_int_to_decimal_3\' failed!");
}
END_TEST

START_TEST(from_int_to_decimal_4) {
  int nbr = -2147483648;
  s21_decimal expected = s21_dec_parse("-2147483648");

  s21_decimal actual;
  int ret = s21_from_int_to_decimal(nbr, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_int_to_decimal_4\' failed!");
}
END_TEST

START_TEST(from_int_to_decimal_5) {
  int nbr = 0;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual = s21_dec_parse("-123");
  int ret = s21_from_int_to_decimal(nbr, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_int_to_decimal_5\' failed!");
}
END_TEST

/*  with_NULL */
START_TEST(from_int_to_decimal_6) {
  int nbr = 1;

  int ret = s21_from_int_to_decimal(nbr, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *s21_test_from_int_to_decimal() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, from_int_to_decimal_1);
  tcase_add_test(case_1, from_int_to_decimal_2);
  tcase_add_test(case_1, from_int_to_decimal_3);
  tcase_add_test(case_1, from_int_to_decimal_4);
  tcase_add_test(case_1, from_int_to_decimal_5);

  TCase *case_2 = tcase_create(C_RED "with_NULL" C_DEFAULT);
  tcase_add_test(case_2, from_int_to_decimal_6);

  Suite *suite = suite_create(C_CYAN "s21_from_int_to_decimal" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  return suite;
}