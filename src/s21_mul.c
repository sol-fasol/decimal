#include "common/s21_arithmetic.h"
#include "s21_decimal.h"

int s21_mul96x96to192(void *a, void *b, void *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int re = 0;
  if (result && s21_dec_isvalid(&value_1) && s21_dec_isvalid(&value_2)) {
    t_u32 flags = s21_xor_signs(&value_1, &value_2);
    s21_decimal dec = {0};
    if (s21_dec_iszero(&value_1) || s21_dec_iszero(&value_2)) {
      s21_dec_set_l64_h32(&dec, 0U, 0U);
      s21_dec_setflags(&dec, flags);
    } else {
      int scale = s21_dec_getscale(&value_1) + s21_dec_getscale(&value_2);
      t_u32 buf[6] = {0};
      int hi_bit = s21_mul96x96to192(&value_1, &value_2, buf);
      s21_dec_setflags(&dec, (flags | ((t_u32)scale << DEC_SCALE_SHIFT)));
      re = s21_scale_result(buf, hi_bit, &dec, 0U);
    }
    if (re == 0) {
      *result = dec;
    } else if ((flags & DEC_SIGN_MASK)) {
      ++re;
    }
  }
  return re;
}

int s21_mul96x96to192(void *a, void *b, void *result) {
  t_u64 tmp = (t_u64)s21_get32(a, 0) * s21_get32(b, 0);
  s21_set32(result, 0, (t_u32)tmp);

  t_u64 tmp2 = (t_u64)s21_get32(a, 0) * s21_get32(b, 1);
  tmp2 += (tmp >> DEC_BIT_SHIFT);
  tmp = (t_u64)s21_get32(a, 1) * s21_get32(b, 0);
  tmp += tmp2;
  s21_set32(result, 1, (t_u32)tmp);

  t_u64 carry = (tmp < tmp2);
  tmp2 = (carry << DEC_BIT_SHIFT) | (tmp >> DEC_BIT_SHIFT);
  tmp = (t_u64)s21_get32(a, 1) * s21_get32(b, 1) + tmp2;
  tmp2 = (t_u64)s21_get32(a, 0) * s21_get32(b, 2);
  tmp += tmp2;
  carry = (tmp < tmp2);
  tmp2 = (t_u64)s21_get32(a, 2) * s21_get32(b, 0);
  tmp += tmp2;
  s21_set32(result, 2, (t_u32)tmp);

  carry += (tmp < tmp2);
  tmp2 = (carry << DEC_BIT_SHIFT) | (tmp >> DEC_BIT_SHIFT);
  tmp = (t_u64)s21_get32(a, 1) * s21_get32(b, 2);
  tmp += tmp2;
  carry = (tmp < tmp2);
  tmp2 = (t_u64)s21_get32(a, 2) * s21_get32(b, 1);
  tmp += tmp2;
  s21_set32(result, 3, (t_u32)tmp);

  carry += (tmp < tmp2);
  tmp = (carry << DEC_BIT_SHIFT) | (tmp >> DEC_BIT_SHIFT);
  tmp += (t_u64)s21_get32(a, 2) * s21_get32(b, 2);
  s21_set64(result, 4, tmp);

  return s21_get_high_bit(result, 6);
}