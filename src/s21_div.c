#include "common/s21_arithmetic.h"
#include "s21_decimal.h"

int s21_div_96by96(void *dec, void *divisor, s21_decimal *result);
t_u32 s21_div_by96(void *dec, void *den, int *scale);
t_u32 s21_div_by64(void *dec, void *den, int *scale);
t_u32 s21_div_by32(void *dec, t_u32 den, int *scale);
void s21_normalise(void *dec, void *div);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int re = 0;
  s21_decimal dec = {0};
  if (result && s21_dec_isvalid(&value_1) && s21_dec_isvalid(&value_2)) {
    if (s21_dec_iszero(&value_2)) {
      re = 3;
    } else if (s21_dec_iszero(&value_1)) {
      s21_dec_set_l64_h32(&dec, 0U, 0U);
      s21_dec_setflags(&dec, s21_xor_signs(&value_1, &value_2));
    } else {
      re = s21_div_96by96(&value_1, &value_2, &dec);
    }
    if (re == 0) {
      *result = dec;
    }
  }
  return re;
}

int s21_div_96by96(void *dec, void *divisor, s21_decimal *result) {
  int scale = s21_dec_getscale(dec) - s21_dec_getscale(divisor);
  t_u32 xor_signs = s21_xor_signs(dec, divisor);
  t_u32 buf[6] = {0};
  s21_buf_cpy(dec, buf, 3);
  t_u32 sticky;
  if (s21_get64(divisor, 1) == 0) {
    sticky = s21_div_by32(buf, s21_get32(divisor, 0), &scale);
  } else if (s21_get32(divisor, 2) == 0) {
    sticky = s21_div_by64(buf, divisor, &scale);
  } else {
    sticky = s21_div_by96(buf, divisor, &scale);
  }
  int hi_bit = s21_get_high_bit(buf, 6);
  if (scale < 0) {
    s21_dec_apply_scale_to192(buf, -scale, &hi_bit);
    scale = 0;
  }
  s21_dec_setflags(result, xor_signs);
  s21_dec_setscale(result, scale);
  int re = s21_scale_result(buf, hi_bit, result, sticky);
  if (re && xor_signs) {
    ++re;
  }
  return re;
}

t_u32 s21_div_by32(void *dec, t_u32 den, int *scale) {
  int hi_bit = s21_get_high_bit(dec, 3);
  t_u32 rem = s21_divmod_96by32(dec, den);
  while (rem && hi_bit < 3) {
    s21_dec_apply_scale_to192(dec, 9, &hi_bit);
    *scale += 9;
    t_u64 num = (t_u64)rem * UINT_10_POW_9;
    t_u32 div = (t_u32)(num / den);
    s21_add_32to192(dec, &hi_bit, div);
    rem = (t_u32)num - div * den;
  }
  return rem;
}

t_u32 s21_div_by64(void *dec, void *den, int *scale) {
  s21_normalise(dec, den);
  t_u32 rem[6] = {0};
  s21_buf_cpy(dec, rem, 4);
  t_u64 divisor = s21_get64(den, 0);
  s21_set32(dec, 2, 0);
  s21_set32(dec, 1, s21_divmod_96by64(rem + 1, divisor));
  s21_set32(dec, 0, s21_divmod_96by64(rem, divisor));
  int rem_hi_bit = s21_get_high_bit(rem, 3);
  int res_hi_bit = s21_get_high_bit(dec, 3);
  while (s21_get64(rem, 0) && res_hi_bit < 3) {
    s21_dec_apply_scale_to192(rem, 9, &rem_hi_bit);
    s21_dec_apply_scale_to192(dec, 9, &res_hi_bit);
    *scale += 9;
    t_u32 div = s21_divmod_96by64(rem, divisor);
    s21_add_32to192(dec, &res_hi_bit, div);
  }
  return (t_u32)(s21_get64(rem, 0) != 0);
}

t_u32 s21_div_by96(void *dec, void *den, int *scale) {
  s21_normalise(dec, den);
  t_u32 rem[6] = {0};
  s21_buf_cpy(dec, rem, 4);
  s21_set64(dec, 0, s21_divmod_128by96(rem, den));
  s21_set64(dec, 2, 0);
  int rem_hi_bit = s21_get_high_bit(rem, 4);
  int res_hi_bit = s21_get_high_bit(dec, 4);
  while (!s21_dec_iszero(rem) && res_hi_bit < 3) {
    s21_dec_apply_scale_to192(rem, 9, &rem_hi_bit);
    s21_dec_apply_scale_to192(dec, 9, &res_hi_bit);
    *scale += 9;
    t_u32 div = s21_divmod_128by96(rem, den);
    s21_add_32to192(dec, &res_hi_bit, div);
  }
  return !s21_dec_iszero(rem);
}

void s21_normalise(void *dec, void *den) {
  t_u32 hi = s21_get32(den, 2);
  if (hi == 0U) {
    hi = s21_get32(den, 1);
  }
  int shift = s21_leading_zero_count(hi);
  t_u64 low = s21_get64(den, 0) << shift;
  t_u64 high = s21_get64(den, 1) >> (DEC_BIT_SHIFT - shift);
  s21_dec_set_l64_h32(den, low, (t_u32)high);
  low = s21_get64(dec, 0) << shift;
  high = s21_get64(dec, 1) >> (DEC_BIT_SHIFT - shift);
  s21_set64(dec, 0, low);
  s21_set64(dec, 2, high);
}