#include "s21_scaling.h"

#include "s21_arithmetic.h"

int s21_scale_result(t_u32 *d, int hi_bit, s21_decimal *dec, t_u32 sticky) {
  int re = 0;
  int scale = s21_dec_getscale(dec);
  while (hi_bit >= 3 || scale > 28) {
    t_u32 power = 0U;
    if ((hi_bit > 3 && scale > 9) || scale > 28 + 9) {
      power = UINT_10_POW_9;
      scale -= 9;
    } else if (scale > 28) {
      power = s21_get_power(scale - 28);
      scale = 28;
    } else if (scale) {
      power = 10;
      --scale;
    } else {
      re = 1;
      hi_bit = 0;
    }
    if (re == 0) {
      t_u32 remainder = s21_divmod_192by32(d, &hi_bit, power);
      if (hi_bit >= 3 || scale > 28) {
        sticky |= remainder;
      } else if (power < remainder * 2 + !!(sticky | (d[0] & 1))) {
        s21_round_up(d, &hi_bit);
        sticky = 0U;
      }
    }
  }
  if (re == 0) {
    s21_buf_cpy(d, dec, 3);
    s21_dec_setscale(dec, scale);
    s21_dec_unscale(dec);
  }
  return re;
}

void s21_192round_by(void *d, int hi_bit, int scale, int mode) {
  t_u32 remainder = 0U;
  t_u32 sticky = 0U;
  t_u32 power = 0U;
  while (scale >= 9) {
    scale -= 9;
    power = UINT_10_POW_9;
    remainder = s21_divmod_192by32(d, &hi_bit, power);
    if (scale) {
      sticky |= remainder;
    }
  }
  if (scale) {
    power = s21_get_power(scale);
    remainder = s21_divmod_192by32(d, &hi_bit, power);
  }
  if (mode == DEC_ROUND_TO_EVEN) {
    if (power < remainder * 2 + !!(sticky | (s21_get32(d, 0) & 1))) {
      s21_round_up(d, &hi_bit);
    }
  } else if (mode == DEC_ROUND_TO_INF) {
    if ((remainder | sticky)) {
      s21_round_up(d, &hi_bit);
    }
  }
}

void s21_dec_apply_scale_to192(void *dec, int scale, int *hi_bit) {
  t_u32 *d = (t_u32 *)dec;
  while (scale) {
    t_u64 power;
    if (scale >= 9) {
      power = UINT_10_POW_9;
      scale -= 9;
    } else {
      power = s21_get_power(scale);
      scale = 0;
    }
    t_u64 tmp = 0UL;
    int cur = 0;
    while (cur <= *hi_bit) {
      tmp += power * d[cur];
      d[cur] = (t_u32)tmp;
      ++cur;
      tmp >>= DEC_BIT_SHIFT;
    }
    if (tmp) {
      d[++(*hi_bit)] = (t_u32)tmp;
    }
  }
}

void s21_dec_unscale(s21_decimal *d) {
  const int *low = d->bits;
  int scale = s21_dec_getscale(d);
  while (!(*low & 0xf) && scale >= 4 && s21_div_by_const(d, 10000U)) {
    scale -= 4;
  }
  if (!(*low & 3) && scale >= 2 && s21_div_by_const(d, 100U)) {
    scale -= 2;
  }
  if (!(*low & 1) && scale >= 1 && s21_div_by_const(d, 10U)) {
    --scale;
  }
  s21_dec_setscale(d, scale);
}

void s21_round_up(void *d, int *hi_bit) {
  t_u32 *d192 = (t_u32 *)d;
  int cur = 0;
  while (!(++d192[cur])) {
    ++cur;
  }
  if (cur > *hi_bit) {
    *hi_bit = cur;
  }
}

t_u32 s21_get_power(int scale) {
  static const t_u32 powers[10] = UINT_POWERS_OF_10;
  return powers[scale];
}

int s21_leading_zero_count(t_u32 num) {
  int re = 0;
  while (!(num & DEC_SIGN_MASK)) {
    ++re;
    num <<= 1;
  }
  return re;
}