#include "common/s21_getset.h"
#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int re = 1;
  if (dst && s21_truncate(src, &src) == 0 && s21_get64(&src, 1) == 0) {
    int val = (int)s21_get32(&src, 0);
    re = (s21_dec_getsign(&src) ? ((val = -val) > 0) : (val < 0));
    if (re == 0) {
      *dst = val;
    }
  }
  return re;
}