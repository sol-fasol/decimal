#include "s21_test.h"

/*  general */
START_TEST(from_float_to_decimal_1) {
  float flo = 123.f;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_1\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float flo = 123.456789e16f;
  s21_decimal expected = s21_dec_parse("1234568000000000000");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_2\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float flo = -1e15f;
  s21_decimal expected = s21_dec_parse("-1000000000000000");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_3\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float flo = 123e25f;
  s21_decimal expected = s21_dec_parse("1230000000000000000000000000");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_4\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  float flo = 123456e-29f;
  s21_decimal expected = s21_dec_parse("0.0000000000000000000000012346");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_5\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  float flo = 12345675.f;
  s21_decimal expected = s21_dec_parse("12345680");

  s21_decimal actual;
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_6\' failed!");
}
END_TEST

/*  with_overflow */
START_TEST(from_float_to_decimal_7) {
  float flo = 1e-29f;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_7\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  float flo = 9.99999999999e28f;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_8\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_9) {
  float flo = -INFINITY;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_9\' failed!");
}
END_TEST

/*  with_NULL_or_NaN */
START_TEST(from_float_to_decimal_10) {
  float flo = NAN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_from_float_to_decimal(flo, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual),
                "Test \'from_float_to_decimal_10\' failed!");
}
END_TEST

START_TEST(from_float_to_decimal_11) {
  float flo = 1.f;

  int ret = s21_from_float_to_decimal(flo, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *s21_test_from_float_to_decimal() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, from_float_to_decimal_1);
  tcase_add_test(case_1, from_float_to_decimal_2);
  tcase_add_test(case_1, from_float_to_decimal_3);
  tcase_add_test(case_1, from_float_to_decimal_4);
  tcase_add_test(case_1, from_float_to_decimal_5);
  tcase_add_test(case_1, from_float_to_decimal_6);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, from_float_to_decimal_7);
  tcase_add_test(case_2, from_float_to_decimal_8);
  tcase_add_test(case_2, from_float_to_decimal_9);

  TCase *case_3 = tcase_create(C_RED "with_NULL_or_NaN" C_DEFAULT);
  tcase_add_test(case_3, from_float_to_decimal_10);
  tcase_add_test(case_3, from_float_to_decimal_11);

  Suite *suite = suite_create(C_CYAN "s21_from_float_to_decimal" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  suite_add_tcase(suite, case_3);
  return suite;
}