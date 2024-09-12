#include "common/s21_arithmetic.h"
#include "s21_decimal.h"

int s21_dec_addsub(s21_decimal *d1, s21_decimal *d2, s21_decimal *result);
int s21_aligned_add(s21_decimal *dec, s21_decimal *addend);
void s21_aligned_sub(s21_decimal *dec, s21_decimal *subtrahend);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int re = 0;
  if (result && s21_dec_isvalid(&value_1) && s21_dec_isvalid(&value_2)) {
    re = s21_dec_addsub(&value_1, &value_2, result);
  }
  return re;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int re = 0;
  if (result && s21_dec_isvalid(&value_1) && s21_dec_isvalid(&value_2)) {
    s21_dec_negate(&value_2);
    re = s21_dec_addsub(&value_1, &value_2, result);
  }
  return re;
}

int s21_dec_addsub(s21_decimal *d1, s21_decimal *d2, s21_decimal *result) {
  int re = 0;
  t_u32 xor_signs = s21_xor_signs(d1, d2);
  int d_scale = s21_dec_getscale(d2) - s21_dec_getscale(d1);
  if (d_scale < 0) {
    s21_swap(&d1, &d2);
    d_scale = -d_scale;
  }
  t_u32 buf[6] = {0};
  s21_buf_cpy(d1, buf, 3);
  int hiprod = s21_get_high_bit(buf, 3);
  s21_dec_apply_scale_to192(buf, d_scale, &hiprod);
  if (d_scale == 0 || hiprod < 3) {
    s21_buf_cpy(buf, d1, 3);
    if (xor_signs) {
      s21_aligned_sub(d1, d2);
    } else {
      re = s21_aligned_add(d1, d2);
    }
  } else {
    if (xor_signs) {
      s21_sub_96from192(buf, hiprod, d2);
    } else {
      re = s21_add_96to192(buf, hiprod, d2);
    }
  }
  if (re == 0) {
    *result = *d2;
  }
  return re;
}

int s21_aligned_add(s21_decimal *dec, s21_decimal *addend) {
  int re = 0;
  t_u64 dec_low64 = s21_get64(dec, 0);
  t_u32 dec_high32 = s21_get32(dec, 2);
  t_u64 low64 = dec_low64 + s21_get64(addend, 0);
  t_u32 high32 = dec_high32 + s21_get32(addend, 2);

  if ((low64 < dec_low64 && ++high32 <= dec_high32) || high32 < dec_high32) {
    int scale = s21_dec_getscale(addend);
    if (scale) {
      s21_dec_setscale(addend, scale - 1);
      t_u32 buf[4] = {0};
      buf[3] = 1;
      s21_dec_set_l64_h32(buf, low64, high32);
      s21_192round_by(buf, 3, 1, DEC_ROUND_TO_EVEN);
      low64 = s21_get64(buf, 0);
      high32 = buf[2];
    } else {
      re = 1 + s21_dec_getsign(addend);
    }
  }
  if (re == 0) {
    s21_dec_set_l64_h32(addend, low64, high32);
  }
  return re;
}

void s21_aligned_sub(s21_decimal *dec, s21_decimal *subtrahend) {
  t_u64 dec_low64 = s21_get64(dec, 0);
  t_u32 dec_high32 = s21_get32(dec, 2);
  t_u64 low64 = dec_low64 - s21_get64(subtrahend, 0);
  t_u32 high32 = dec_high32 - s21_get32(subtrahend, 2);

  if ((low64 > dec_low64 && --high32 >= dec_high32) || high32 > dec_high32) {
    high32 = ~high32;
    if ((low64 = (t_u64) - (long)low64) == 0UL) {
      ++high32;
    }
  } else {
    s21_dec_negate(subtrahend);
  }
  s21_dec_set_l64_h32(subtrahend, low64, high32);
}
