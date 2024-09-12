#include "s21_arithmetic.h"
#include "s21_scaling.h"

int s21_dec_set_l64_h64(void *dec, t_u64 low, t_u64 high);

void s21_set32(void *dec, int i, t_u32 val) { ((t_u32 *)dec)[i] = val; }

void s21_set64(void *dec, int i, t_u64 val) {
  t_u32 *bits = (t_u32 *)dec;
  bits[i] = (t_u32)val;
  bits[i + 1] = (t_u32)(val >> DEC_BIT_SHIFT);
}

void s21_dec_set_l32_h64(void *dec, t_u32 low, t_u64 high) {
  t_u32 *bits = (t_u32 *)dec;
  bits[0] = low;
  bits[1] = (t_u32)high;
  bits[2] = (t_u32)(high >> DEC_BIT_SHIFT);
}

void s21_dec_set_l64_h32(void *dec, t_u64 low, t_u32 high) {
  t_u32 *bits = (t_u32 *)dec;
  bits[0] = (t_u32)low;
  bits[1] = (t_u32)(low >> DEC_BIT_SHIFT);
  bits[2] = high;
}

void s21_dec_setscale(void *d, int scale) {
  t_u32 *bits = (t_u32 *)d;
  bits[3] &= DEC_SIGN_MASK;
  bits[3] |= ((t_u32)scale << DEC_SCALE_SHIFT);
}

void s21_dec_setflags(void *d, t_u32 flags) {
  t_u32 *bits = (t_u32 *)d;
  bits[3] = flags;
}

void s21_dec_negate(void *d) {
  t_u32 *bits = (t_u32 *)d;
  bits[3] ^= DEC_SIGN_MASK;
}

void s21_buf_cpy(const void *src, void *dst, int n) {
  const t_u32 *buf_src = (const t_u32 *)src;
  t_u32 *buf_dst = (t_u32 *)dst;
  while (n--) {
    buf_dst[n] = buf_src[n];
  }
}

int s21_dec_set_u32_scale(s21_decimal *dec, t_u64 mant, int scale) {
  int re = 0;
  if (scale < 0) {
    scale = -scale;
    if (scale < 10) {
      t_u64 low64 = mant * s21_get_power(scale);
      s21_dec_set_l64_h32(dec, low64, 0);
    } else if (scale > 18) {
      t_u64 low64 = mant * s21_get_power(scale - 18);
      re = s21_mul64x64to96(low64, ULONG_10_POW_18, dec);
    } else {
      t_u64 low64 = mant * s21_get_power(scale - 9);
      t_u64 high64 = (low64 >> 32) * UINT_10_POW_9;
      low64 = (t_u64)UINT_10_POW_9 * (t_u32)low64;
      re = s21_dec_set_l64_h64(dec, low64, high64);
    }
  } else if ((re = (scale > 28)) == 0) {
    s21_dec_setscale(dec, scale);
    s21_dec_set_l64_h32(dec, mant, 0U);
    s21_dec_unscale(dec);
  }
  return re;
}

int s21_dec_set_l64_h64(void *dec, t_u64 low, t_u64 high) {
  t_u64 tmp = (low >> DEC_BIT_SHIFT) + high;
  int re = (tmp < high);
  if (re == 0) {
    s21_dec_set_l32_h64(dec, (t_u32)low, tmp);
  }
  return re;
}

void s21_swap(void *p1, void *p2) {
  void *tmp = *((void **)p1);
  *((void **)p1) = *((void **)p2);
  *((void **)p2) = tmp;
}