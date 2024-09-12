#include "common/s21_arithmetic.h"
#include "s21_decimal.h"

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int re = 0;
  if (s21_dec_isvalid(&d1) && s21_dec_isvalid(&d2)) {
    re = (s21_dec_cmp(&d1, &d2) == 0);
  }
  return re;
}