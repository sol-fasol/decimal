#ifndef S21_ARITHMETIC_H

#define S21_ARITHMETIC_H

#include "../s21_decimal.h"
#include "s21_getset.h"
#include "s21_scaling.h"

int s21_mul64x64to96(t_u64 a, t_u64 b, s21_decimal *res);

t_u32 s21_divmod_192by32(void *d, int *hi_bit, t_u32 den);
t_u32 s21_divmod_96by32(void *dec, t_u32 den);

t_u32 s21_divmod_96by64(void *d, t_u64 den);
t_u32 s21_divmod_128by96(void *d, void *den);

int s21_div_by_const(s21_decimal *dec, t_u32 den);

int s21_add_96to192(void *d, int hi_bit, s21_decimal *addend);
void s21_sub_96from192(void *d192, int hi_bit, s21_decimal *subtrahend);

void s21_add_32to192(void *d, int *hi_bit, t_u32 addend);

int s21_dec_cmp(s21_decimal *d1, s21_decimal *d2);

#endif