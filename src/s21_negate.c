#include "common/s21_getset.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int re = 1;
  if (result && s21_dec_isvalid(&value)) {
    s21_dec_negate(&value);
    *result = value;
    re = 0;
  }
  return re;
}