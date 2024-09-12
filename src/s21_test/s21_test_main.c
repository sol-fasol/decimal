#include "s21_test.h"

int main() {
  SRunner *sr = srunner_create(s21_test_negate());
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_add_suite(sr, s21_test_floor());
  srunner_add_suite(sr, s21_test_round());
  srunner_add_suite(sr, s21_test_truncate());

  srunner_add_suite(sr, s21_test_add());
  srunner_add_suite(sr, s21_test_sub());
  srunner_add_suite(sr, s21_test_mul());
  srunner_add_suite(sr, s21_test_div());

  srunner_add_suite(sr, s21_test_is_less());
  srunner_add_suite(sr, s21_test_is_less_or_equal());
  srunner_add_suite(sr, s21_test_is_greater());
  srunner_add_suite(sr, s21_test_is_greater_or_equal());
  srunner_add_suite(sr, s21_test_is_equal());
  srunner_add_suite(sr, s21_test_is_not_equal());

  srunner_add_suite(sr, s21_test_from_int_to_decimal());
  srunner_add_suite(sr, s21_test_from_float_to_decimal());
  srunner_add_suite(sr, s21_test_from_decimal_to_int());
  srunner_add_suite(sr, s21_test_from_decimal_to_float());

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return !!failed;
}

int s21_dec_eq(s21_decimal d1, s21_decimal d2) {
  int re = 0;
  if (s21_dec_isvalid(&d1) && s21_dec_isvalid(&d2)) {
    re = (s21_dec_iszero(&d1) && s21_dec_iszero(&d2));
    if (re == 0) {
      s21_dec_unscale(&d1);
      s21_dec_unscale(&d2);
      re = (memcmp(&d1, &d2, sizeof(s21_decimal)) == 0);
    }
  } else {
    re = (s21_dec_isvalid(&d1) == s21_dec_isvalid(&d2));
  }
  return re;
}

s21_decimal s21_dec_parse(char *str) {
  s21_decimal dec = {0};
  char *ptr = str;
  int sign = (*ptr == '-');
  ptr += sign;
  int buf[6] = {0};
  int hi_bit = 0;
  unsigned tmp = 0;
  char *p_dot = NULL;
  int state = 1;
  while (state && *ptr) {
    int offset = 0;
    if (sscanf(ptr, "%9u%n", &tmp, &offset) == 1) {
      ptr += offset;
      s21_dec_apply_scale_to192(buf, offset, &hi_bit);
      s21_add_32to192(buf, &hi_bit, tmp);
    } else if (*ptr == '.') {
      p_dot = ++ptr;
    } else {
      state = 0;
    }
  }
  if (sign) {
    buf[3] = (int)0x80000000;
  }
  if (p_dot) {
    buf[3] |= ((int)(ptr - p_dot) << 16);
  }
  s21_buf_cpy(buf, &dec, 4);
  return dec;
}