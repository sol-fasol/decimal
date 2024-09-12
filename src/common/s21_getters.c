#include "s21_getset.h"

t_u32 s21_get32(void *dec, int i) { return (((t_u32 *)dec)[i]); }

t_u64 s21_get64(void *dec, int i) {
  t_u32 *bits = (t_u32 *)dec;
  return (((t_u64)(bits[i + 1]) << DEC_BIT_SHIFT) | bits[i]);
}

int s21_dec_getscale(void *arg) {
  return (int)((s21_dec_getflags(arg) & DEC_SCALE_MASK) >> DEC_SCALE_SHIFT);
}

int s21_dec_getsign(void *arg) {
  return !!(s21_dec_getflags(arg) & DEC_SIGN_MASK);
}

t_u32 s21_dec_getflags(void *arg) { return (((t_u32 *)arg))[3]; }

int s21_get_high_bit(const void *d, int end) {
  const t_u32 *bits = (const t_u32 *)d;
  do {
    --end;
  } while (end && bits[end] == 0U);
  return end;
}

int s21_dec_iszero(const void *arg) {
  const t_u32 *bits = (const t_u32 *)arg;
  return !(bits[0] || bits[1] || bits[2]);
}

int s21_dec_isvalid(void *arg) {
  t_u32 flags = ((t_u32 *)arg)[3];
  int re = 0;
  if (!(flags & ~(DEC_SIGN_MASK | DEC_SCALE_MASK))) {
    re = (flags & DEC_SCALE_MASK) <= (28U << DEC_SCALE_SHIFT);
  }
  return re;
}

t_u32 s21_xor_signs(void *d1, void *d2) {
  return ((((t_u32 *)d1)[3] ^ ((t_u32 *)d2)[3]) & DEC_SIGN_MASK);
}