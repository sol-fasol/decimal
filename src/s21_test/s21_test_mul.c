#include "s21_test.h"

/*  general */
START_TEST(mul_1) {
  s21_decimal d1 = s21_dec_parse("123");
  s21_decimal d2 = s21_dec_parse("3");
  s21_decimal expected = s21_dec_parse("369");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_1\' failed!");
}
END_TEST

START_TEST(mul_2) {
  s21_decimal d1 = s21_dec_parse("-33333333333333333333.000");
  s21_decimal d2 = s21_dec_parse("-3");
  s21_decimal expected = s21_dec_parse("99999999999999999999");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_2\' failed!");
}
END_TEST

START_TEST(mul_3) {
  s21_decimal d1 = s21_dec_parse("0.000000000003");
  s21_decimal d2 = s21_dec_parse("33333333333333333333");
  s21_decimal expected = s21_dec_parse("99999999.999999999999");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_3\' failed!");
}
END_TEST

START_TEST(mul_4) {
  s21_decimal d1 = s21_dec_parse("65654365765654346546563354");
  s21_decimal d2 = s21_dec_parse("0.65635645365436565436564");
  s21_decimal expected = s21_dec_parse("43092666680871478139538601.886");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_4\' failed!");
}
END_TEST

START_TEST(mul_5) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = s21_dec_parse("0");
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_5\' failed!");
}
END_TEST

START_TEST(mul_6) {
  s21_decimal d1 = s21_dec_parse("0");
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_6\' failed!");
}
END_TEST

START_TEST(mul_7) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = s21_dec_parse("-0.5");
  s21_decimal expected = s21_dec_parse("-39614081257132168796771975168");

  s21_decimal actual;
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_7\' failed!");
}
END_TEST

/*  with_overflow */
START_TEST(mul_8) {
  s21_decimal d1 = s21_dec_parse("1.000000000000000000000001");
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 2);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_8\' failed!");
}
END_TEST

START_TEST(mul_9) {
  s21_decimal d1 = S21_DEC_MIN;
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual = s21_dec_parse("1234");
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_9\' failed!");
}
END_TEST

START_TEST(mul_10) {
  s21_decimal d1 = s21_dec_parse("15845632502852867518708790067");
  s21_decimal d2 = s21_dec_parse("-5.0000000000000000000000001");
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual = s21_dec_parse("1234");
  int ret = s21_mul(d1, d2, &actual);

  ck_assert_int_eq(ret, 2);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'mul_10\' failed!");
}
END_TEST

Suite *s21_test_mul() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, mul_1);
  tcase_add_test(case_1, mul_2);
  tcase_add_test(case_1, mul_3);
  tcase_add_test(case_1, mul_4);
  tcase_add_test(case_1, mul_5);
  tcase_add_test(case_1, mul_6);
  tcase_add_test(case_1, mul_7);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, mul_8);
  tcase_add_test(case_2, mul_9);
  tcase_add_test(case_2, mul_10);

  Suite *suite = suite_create(C_CYAN "s21_mul" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}