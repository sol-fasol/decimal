#include "s21_test.h"

/*  general */
START_TEST(div_1) {
  s21_decimal d1 = s21_dec_parse("369");
  s21_decimal d2 = s21_dec_parse("3");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_1\' failed!");
}
END_TEST

START_TEST(div_2) {
  s21_decimal d1 = s21_dec_parse("-1");
  s21_decimal d2 = s21_dec_parse("3");
  s21_decimal expected = s21_dec_parse("-0.3333333333333333333333333333");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_2\' failed!");
}
END_TEST

START_TEST(div_3) {
  s21_decimal d1 = s21_dec_parse("0.000000000000000000000003");
  s21_decimal d2 = s21_dec_parse("-3");
  s21_decimal expected = s21_dec_parse("-0.000000000000000000000001");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_3\' failed!");
}
END_TEST

START_TEST(div_4) {
  s21_decimal d1 = S21_DEC_MIN;
  s21_decimal d2 = S21_DEC_MIN;
  s21_decimal expected = s21_dec_parse("1");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_4\' failed!");
}
END_TEST

START_TEST(div_5) {
  s21_decimal d1 = s21_dec_parse("0");
  s21_decimal d2 = S21_DEC_MAX;
  s21_decimal expected = s21_dec_parse("0");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_5\' failed!");
}
END_TEST

START_TEST(div_6) {
  s21_decimal d1 = s21_dec_parse("123456789012345");
  s21_decimal d2 = s21_dec_parse("1.00000000000002");
  s21_decimal expected = s21_dec_parse("123456789012342.53086421975315");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_6\' failed!");
}
END_TEST

START_TEST(div_7) {
  s21_decimal d1 = s21_dec_parse("-1");
  s21_decimal d2 = s21_dec_parse("0.00000000000005");
  s21_decimal expected = s21_dec_parse("-20000000000000");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_7\' failed!");
}
END_TEST

START_TEST(div_8) {
  s21_decimal d1 = s21_dec_parse("435349584754892549585435");
  s21_decimal d2 = s21_dec_parse("988775654454325454355435");
  s21_decimal expected = s21_dec_parse("0.4402915694714878995558619266");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_8\' failed!");
}
END_TEST

START_TEST(div_9) {
  s21_decimal d1 = s21_dec_parse("654365564643543254656654454");
  ;
  s21_decimal d2 = s21_dec_parse("5123123123");
  s21_decimal expected = s21_dec_parse("127727862269365032.91542198097");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_9\' failed!");
}
END_TEST

START_TEST(div_10) {
  s21_decimal d1 = s21_dec_parse("54353454354698776432540967");
  s21_decimal d2 = s21_dec_parse("35");
  s21_decimal expected = s21_dec_parse("1552955838705679326644027.6286");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_10\' failed!");
}
END_TEST

START_TEST(div_11) {
  s21_decimal d1 = s21_dec_parse("1");
  s21_decimal d2 = s21_dec_parse("4294967296");
  s21_decimal expected = s21_dec_parse("0.0000000002328306436538696289");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_11\' failed!");
}
END_TEST

START_TEST(div_12) {
  s21_decimal d1 = S21_DEC_MAX;  // s21_dec_parse("1");
  s21_decimal d2 = s21_dec_parse("36893488147419103231");
  s21_decimal expected = s21_dec_parse(" 2147483648.0000000000582076609");

  s21_decimal actual;
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 0);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_12\' failed!");
}
END_TEST

/*  with_overflow */
START_TEST(div_13) {
  s21_decimal d1 = s21_dec_parse("10");
  s21_decimal d2 = S21_DEC_MAX_NEG;
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 2);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_13\' failed!");
}
END_TEST

START_TEST(div_14) {
  s21_decimal d1 = s21_dec_parse("-432135454254354354325");
  s21_decimal d2 = s21_dec_parse("-0.000000000006546546546455");
  s21_decimal expected = s21_dec_parse("1234");

  s21_decimal actual = s21_dec_parse("1234");
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 1);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_14\' failed!");
}
END_TEST

/*  with_divide_by_zero */

START_TEST(div_15) {
  s21_decimal d1 = S21_DEC_MAX;
  s21_decimal d2 = s21_dec_parse("0");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 3);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_15\' failed!");
}
END_TEST

START_TEST(div_16) {
  s21_decimal d1 = s21_dec_parse("0");
  s21_decimal d2 = s21_dec_parse("0");
  s21_decimal expected = s21_dec_parse("123");

  s21_decimal actual = s21_dec_parse("123");
  int ret = s21_div(d1, d2, &actual);

  ck_assert_int_eq(ret, 3);
  ck_assert_msg(s21_dec_eq(expected, actual), "Test \'div_16\' failed!");
}
END_TEST

Suite *s21_test_div() {
  TCase *case_1 = tcase_create(C_RED "general" C_DEFAULT);
  tcase_add_test(case_1, div_1);
  tcase_add_test(case_1, div_2);
  tcase_add_test(case_1, div_3);
  tcase_add_test(case_1, div_4);
  tcase_add_test(case_1, div_5);
  tcase_add_test(case_1, div_6);
  tcase_add_test(case_1, div_7);
  tcase_add_test(case_1, div_8);
  tcase_add_test(case_1, div_9);
  tcase_add_test(case_1, div_10);
  tcase_add_test(case_1, div_11);
  tcase_add_test(case_1, div_12);

  TCase *case_2 = tcase_create(C_RED "with_overflow" C_DEFAULT);
  tcase_add_test(case_2, div_13);
  tcase_add_test(case_2, div_14);

  TCase *case_3 = tcase_create(C_RED "with_divide_by_zero" C_DEFAULT);
  tcase_add_test(case_3, div_15);
  tcase_add_test(case_3, div_16);

  Suite *suite = suite_create(C_CYAN "s21_div" C_DEFAULT);
  suite_add_tcase(suite, case_1);
  suite_add_tcase(suite, case_2);
  suite_add_tcase(suite, case_3);

  return suite;
}