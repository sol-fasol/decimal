#include <math.h>

#include "common/s21_getset.h"
#include "s21_decimal.h"

int s21_get_scale(double *n, int *scale);
double s21_apply_decexp(double mant, int exp);
int s21_get_decexp(double n);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int re = !dst;
  t_u32 sign = (t_u32)((src < 0.f) << 31);
  double dbl = (sign ? -src : src);
  s21_decimal dec = {0};
  int scale = 0;
  if (re == 0) {
    if ((re = (dbl < 1e-28 && dbl > 0.))) {
      *dst = dec;
    } else {
      s21_dec_setflags(&dec, sign);
      re = s21_get_scale(&dbl, &scale);
    }
  }
  if (re == 0) {
    t_u32 mant = (t_u32)(int)dbl;
    dbl -= (int)mant;
    if (dbl > 0.5 || (!(dbl < 0.5) && (mant & 1))) {
      mant++;
    }
    if ((re = s21_dec_set_u32_scale(&dec, mant, scale)) == 0) {
      *dst = dec;
    }
  }
  return re;
}

int s21_get_scale(double *n, int *scale) {
  int re = 0;
  double dbl = *n;
  if (isfinite(dbl) && dbl <= 7922816e22f) {
    int sc = 6 - s21_get_decexp(dbl);
    if (sc > 28) {
      sc = 28;
    }
    *n = s21_apply_decexp(dbl, sc);
    *scale = sc;
  } else {
    re = 1;
  }
  return re;
}

int s21_get_decexp(double n) {
  int exp = 0;
  if (n >= 1.) {
    exp = (int)floor(log10(n));
  } else if (n > 0.) {
    exp = -(int)floor(log10(1. / n)) - 1;
  }
  return exp;
}

double s21_apply_decexp(double mant, int exp) {
  if (mant > 0.) {
    if (exp > 0) {
      mant *= pow(10., exp);
    } else if (exp < 0) {
      mant /= pow(10., -exp);
    }
  }
  return mant;
}