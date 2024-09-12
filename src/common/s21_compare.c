#include "s21_arithmetic.h"

int s21_dec_cmpscale(s21_decimal *d1, s21_decimal *d2);
int s21_dec_cmpsub(void *d1, void *d2, int result);

int s21_dec_cmp(s21_decimal *d1, s21_decimal *d2) {
  int re = 0;
  if (s21_dec_iszero(d2)) {
    if (!s21_dec_iszero(d1)) {
      re = s21_dec_getsign(d1) ? -1 : 1;
    }
  } else if (s21_dec_iszero(d1)) {
    re = s21_dec_getsign(d2) ? 1 : -1;
  } else if ((re = !!s21_xor_signs(d1, d2)) == 0) {
    re = s21_dec_cmpscale(d1, d2);
  } else if (s21_dec_getsign(d1)) {
    re = -1;
  }
  return re;
}

int s21_dec_cmpscale(s21_decimal *d1, s21_decimal *d2) {
  int re = s21_dec_getsign(d1) ? -1 : 1;
  int d_scale = s21_dec_getscale(d2) - s21_dec_getscale(d1);
  if (d_scale < 0) {
    s21_swap(&d1, &d2);
    re = -re;
    d_scale = -d_scale;
  }
  if (d_scale) {
    t_u32 buf[6] = {0};
    s21_buf_cpy(d1, buf, 3);
    int hi_bit = s21_get_high_bit(buf, 3);
    s21_dec_apply_scale_to192(buf, d_scale, &hi_bit);
    if (hi_bit < 3) {
      re = s21_dec_cmpsub(buf, d2, re);
    }
  } else {
    re = s21_dec_cmpsub(d1, d2, re);
  }
  return re;
}

int s21_dec_cmpsub(void *d1, void *d2, int result) {
  t_u64 low64 = s21_get64(d1, 0);
  t_u32 high32 = s21_get32(d1, 2);
  t_u32 d_high = high32 - s21_get32(d2, 2);
  if (d_high) {
    if (d_high > high32) {
      result = -result;
    }
  } else {
    t_u64 d_low = low64 - s21_get64(d2, 0);
    if (d_low == 0) {
      result = 0;
    } else if (d_low > low64) {
      result = -result;
    }
  }
  return result;
}