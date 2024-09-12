#include "s21_arithmetic.h"

int s21_mul64x64to96(t_u64 a, t_u64 b, s21_decimal *res) {
  int re = 1;
  t_u64 low = (t_u64)(t_u32)a * (t_u32)b;
  t_u64 mid = (b >> DEC_BIT_SHIFT) * (t_u32)a;
  t_u64 high = (a >> DEC_BIT_SHIFT) * (b >> DEC_BIT_SHIFT);

  high += (mid >> DEC_BIT_SHIFT);
  mid <<= DEC_BIT_SHIFT;
  low += mid;
  high += (low < mid);

  mid = (a >> DEC_BIT_SHIFT) * (t_u32)b;
  high += (mid >> DEC_BIT_SHIFT);
  mid <<= DEC_BIT_SHIFT;
  low += mid;
  high += (low < mid);

  if ((high >> DEC_BIT_SHIFT) == 0) {
    s21_dec_set_l64_h32(res, low, (t_u32)high);
    re = 0;
  }
  return re;
}

t_u32 s21_divmod_96by32(void *dec, t_u32 den) {
  t_u64 tmp = 0UL;
  t_u64 div = 0UL;
  if (s21_get32(dec, 2) == 0) {
    tmp = s21_get64(dec, 0);
    if (tmp) {
      div = tmp / den;
      s21_dec_set_l64_h32(dec, div, 0U);
    }
  } else {
    tmp = s21_get64(dec, 1);
    div = tmp / den;
    tmp = ((tmp - den * (t_u32)div) << 32) + s21_get32(dec, 0);
    t_u32 div32 = 0U;
    if (tmp) {
      div32 = (t_u32)(tmp / den);
    }
    s21_dec_set_l32_h64(dec, div32, div);
    div = div32;
  }
  return (t_u32)(tmp - div * den);
}

t_u32 s21_divmod_192by32(void *d, int *hi_bit, t_u32 den) {
  t_u32 *d192 = (t_u32 *)d;
  int cur = *hi_bit;
  t_u64 tmp = d192[cur];
  t_u32 div = 0UL;
  while (cur) {
    div = (t_u32)(tmp / den);
    d192[cur] = div;
    tmp = ((tmp - den * div) << DEC_BIT_SHIFT) + d192[--cur];
  }
  div = (t_u32)(tmp / den);
  d192[cur] = div;
  if (*hi_bit && d192[*hi_bit] == 0U) {
    --(*hi_bit);
  }
  return (t_u32)(tmp - div * den);
}

int s21_div_by_const(s21_decimal *dec, t_u32 den) {
  int re = 0;
  t_u32 low32 = s21_get32(dec, 0);
  t_u64 high64 = s21_get64(dec, 1);
  t_u64 div64 = high64 / den;
  t_u32 div32 = (t_u32)((((high64 - div64 * den) << 32) + low32) / den);
  if (low32 == div32 * den) {
    s21_dec_set_l32_h64(dec, div32, div64);
    re = 1;
  }
  return re;
}

t_u32 s21_divmod_96by64(void *d, t_u64 den) {
  t_u32 re = 0;
  t_u64 num = s21_get64(d, 0);
  t_u32 num_high = s21_get32(d, 2);
  t_u32 den_high = (t_u32)(den >> DEC_BIT_SHIFT);
  if (num_high == 0) {
    if (num >= den) {
      re = (t_u32)(num / den);
      num -= den * re;
    }
  } else if ((num = s21_get64(d, 1)) >= den_high) {
    re = (t_u32)(num / den_high);
    num = ((num - re * den_high) << DEC_BIT_SHIFT) | s21_get32(d, 0);
    t_u64 prod = (t_u64)re * (t_u32)den;
    num -= prod;
    if (num > ~prod) {
      do {
        --re;
        num += den;
      } while (num >= den);
    }
  }
  s21_dec_set_l64_h32(d, num, 0U);
  return re;
}

t_u32 s21_divmod_128by96(void *d, void *den) {
  t_u32 *dividend = (t_u32 *)d;
  t_u64 num = s21_get64(dividend, 2);
  t_u32 den_high = s21_get32(den, 2);
  t_u32 re = 0U;
  if (num >= den_high) {
    re = (t_u32)(num / den_high);
    t_u32 rem = (t_u32)num - den_high * re;

    t_u64 pr_low = (t_u64)s21_get32(den, 0) * re;
    t_u64 pr_high = (t_u64)s21_get32(den, 1) * re;
    pr_high += (pr_low >> DEC_BIT_SHIFT);
    pr_low = (pr_high << DEC_BIT_SHIFT) | (t_u32)pr_low;
    pr_high >>= DEC_BIT_SHIFT;

    num = s21_get64(dividend, 0);
    num -= pr_low;
    rem -= (t_u32)pr_high;

    pr_high = ~(t_u32)pr_high;
    if ((num > ~pr_low && --rem >= pr_high) || rem > pr_high) {
      t_u64 den_low = s21_get64(den, 0);
      do {
        --re;
        num += den_low;
        rem += den_high;
      } while ((num >= den_low && ++rem > den_high) || rem >= den_high);
    }
    s21_dec_set_l64_h32(d, num, rem);
    dividend[3] = 0U;
  }
  return re;
}

int s21_add_96to192(void *d, int hi_bit, s21_decimal *addend) {
  int re = 0;
  t_u64 dec_low64 = s21_get64(d, 0);
  t_u32 dec_high32 = s21_get32(d, 2);
  t_u64 low64 = dec_low64 + s21_get64(addend, 0);
  t_u32 high32 = dec_high32 + s21_get32(addend, 2);

  if ((low64 < dec_low64 && ++high32 <= dec_high32) || high32 < dec_high32) {
    int h = hi_bit - 3;
    s21_round_up((t_u32 *)d + 3, &h);
    hi_bit = h + 3;
  }
  s21_dec_set_l64_h32(d, low64, high32);
  re = s21_scale_result(d, hi_bit, addend, 0U);
  if (re == 1 && s21_dec_getsign(addend)) {
    re = 2;
  }
  return re;
}

void s21_sub_96from192(void *d, int hi_bit, s21_decimal *subtrahend) {
  s21_dec_negate(subtrahend);
  t_u64 dec_low64 = s21_get64(d, 0);
  t_u32 dec_high32 = s21_get32(d, 2);
  t_u64 low64 = dec_low64 - s21_get64(subtrahend, 0);
  t_u32 high32 = dec_high32 - s21_get32(subtrahend, 2);

  if ((low64 > dec_low64 && --high32 >= dec_high32) || high32 > dec_high32) {
    int cur = 3;
    t_u32 *d192 = (t_u32 *)d;
    while (d192[cur] == 0U) {
      --(d192[cur]);
      ++cur;
    }
    if (--(d192[cur]) == 0U && cur == hi_bit) {
      --hi_bit;
    }
  }
  if (hi_bit >= 3) {
    s21_dec_set_l64_h32(d, low64, high32);
    s21_scale_result(d, hi_bit, subtrahend, 0U);
  } else {
    s21_dec_set_l64_h32(subtrahend, low64, high32);
  }
}

void s21_add_32to192(void *d, int *hi_bit, t_u32 addend) {
  t_u32 *d192 = (t_u32 *)d;
  if ((*d192 += addend) < addend) {
    int cur = 1;
    while (!(++d192[cur])) {
      ++cur;
    }
    if (cur > *hi_bit) {
      *hi_bit = cur;
    }
  }
}