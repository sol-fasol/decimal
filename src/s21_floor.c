#include "common/s21_scaling.h"
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int re = 1;
  if (result && s21_dec_isvalid(&value)) {
    int scale = s21_dec_getscale(&value);
    if (scale) {
      int mode = s21_dec_getsign(&value) ? DEC_ROUND_TO_INF : 0;
      s21_192round_by(&value, 2, scale, mode);
      s21_dec_setscale(&value, 0);
    }
    *result = value;
    re = 0;
  }
  return re;
}
