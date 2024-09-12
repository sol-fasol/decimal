#include <math.h>

#include "common/s21_getset.h"
#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int re = 1;
  if (dst && s21_dec_isvalid(&src)) {
    double dbl = (double)s21_get32(&src, 2) * 18446744073709551616.;
    dbl += (double)s21_get64(&src, 0);
    dbl /= pow(10., s21_dec_getscale(&src));
    if (s21_dec_getsign(&src)) {
      dbl = -dbl;
    }
    *dst = (float)dbl;
    re = 0;
  }
  return re;
}