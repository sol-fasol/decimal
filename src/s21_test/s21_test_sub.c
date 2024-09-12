#include "s21_test.h"

/*  general */
START_TEST(sub_1) {
  s21_decimal d1 = s21_dec_parse("0000123");
  s21_decimal d2 = s21_dec_parse("0000123");
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_1\' failed!");
}
END_TEST

START_TEST(sub_2) {
  s21_decimal d1 = s21_dec_parse("00000033333333333333333333.000");
  s21_decimal d2 = s21_dec_parse("-0000033333333333333333333");
  s21_decimal expected = s21_dec_parse("66666666666666666666");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_2\' failed!");
}
END_TEST

START_TEST(sub_3) {
  s21_decimal d1 = s21_dec_parse("00000033333333333333333333");
  s21_decimal d2 = s21_dec_parse("00000000000000000000000000.0333333335");
  s21_decimal expected = s21_dec_parse("33333333333333333332.966666666");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_3\' failed!");
}
END_TEST

START_TEST(sub_4) {
  s21_decimal d1 = s21_dec_parse("00000022222222222222222222");
  s21_decimal d2 = s21_dec_parse("00000000000000000000000000.0222222225");
  s21_decimal expected = s21_dec_parse("22222222222222222221.977777778");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_4\' failed!");
}
END_TEST

START_TEST(sub_5) {
  s21_decimal d1 = s21_dec_parse("0000000792281625142643375935.43950334");
  s21_decimal d2 = s21_dec_parse("0000000792281625142643375935.43950335");
  s21_decimal expected = s21_dec_parse("-000000000000000000000.00000001");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_5\' failed!");
}
END_TEST

START_TEST(sub_6) {
  s21_decimal d1 = s21_dec_parse("0000000079228162514264337593.543950335");
  s21_decimal d2 = s21_dec_parse("0000000792281625142643375935.43950335");
  s21_decimal expected = s21_dec_parse("-713053462628379038341.89555302");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_6\' failed!");
}
END_TEST

START_TEST(sub_7) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = s21_dec_parse("0.6");
  s21_decimal expected = s21_dec_parse("79228162514264337593543950334");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_7\' failed!");
}
END_TEST

START_TEST(sub_8) {
  s21_decimal d1 = s21_dec_parse("0");
  s21_decimal d2 = s21_dec_parse("18446744073709551616");
  s21_decimal expected = s21_dec_parse("-18446744073709551616");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_8\' failed!");
}
END_TEST

START_TEST(sub_9) {
  s21_decimal d1 = s21_dec_parse("9134385233318143238773030205");
  s21_decimal d2 = s21_dec_parse("0.9234564345443234564");
  s21_decimal expected = s21_dec_parse("9134385233318143238773030204");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_9\' failed!");
}
END_TEST

START_TEST(sub_10) {
  s21_decimal d1 = s21_dec_parse("7922816251426433759354395034");
  s21_decimal d2 = s21_dec_parse("2.9");
  s21_decimal expected = s21_dec_parse("7922816251426433759354395031.1");

  s21_decimal actual;
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_10\' failed!");
}
END_TEST

/*  with_overflow */
START_TEST(sub_11) {
  s21_decimal d1 = s21_dec_parse("0.5");
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_11\' failed!");
}
END_TEST

START_TEST(sub_12) {
  s21_decimal d1 = S21_DEC_MIN;
  s21_decimal d2 = S21_DEC_MAX;
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual = s21_dec_parse("1234");
  int ret = s21_sub(d1, d2, &actual);

  ck_assert_int_eq(ret, 2);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'sub_12\' failed!");
}
END_TEST

Suite *s21_test_sub() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, sub_1);
  tcase_add_test(case_1, sub_2);
  tcase_add_test(case_1, sub_3);
  tcase_add_test(case_1, sub_4);
  tcase_add_test(case_1, sub_5);
  tcase_add_test(case_1, sub_6);
  tcase_add_test(case_1, sub_7);
  tcase_add_test(case_1, sub_8);
  tcase_add_test(case_1, sub_9);
  tcase_add_test(case_1, sub_10);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, sub_11);
  tcase_add_test(case_2, sub_12);

  Suite *suite = suite_create(C_CYAN "s21_sub" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);

  return suite;
}