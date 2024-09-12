#include "common/s21_getset.h"
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int re = 1;
  if (dst) {
    t_u32 flags = 0;
    if (src < 0) {
      src = -src;
      flags = DEC_SIGN_MASK;
    }
    s21_dec_setflags(dst, flags);
    s21_dec_set_l32_h64(dst, (t_u32)src, 0);
    re = 0;
  }
  return re;
}