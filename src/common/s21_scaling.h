#ifndef S21_SCALING_H

#define S21_SCALING_H

#include "../s21_decimal.h"
#include "s21_getset.h"

#define UINT_10_POW_9 1000000000U
#define ULONG_10_POW_18 1000000000000000000UL
#define UINT_POWERS_OF_10                                                   \
  {                                                                         \
    1U, 10U, 100U, 1000U, 10000U, 100000U, 1000000U, 10000000U, 100000000U, \
        1000000000U                                                         \
  }

#define DEC_ROUND_TO_ZERO 0
#define DEC_ROUND_TO_EVEN 1
#define DEC_ROUND_TO_INF 2

int s21_scale_result(t_u32 *d, int hi_bit, s21_decimal *dec, t_u32 sticky);
void s21_192round_by(void *d, int hiprod, int scale, int mode);
void s21_dec_unscale(s21_decimal *d);
void s21_dec_apply_scale_to192(void *d, int scale, int *out_hiprod);

t_u32 s21_get_power(int scale);
void s21_round_up(void *d, int *hi_bit);
int s21_leading_zero_count(t_u32 num);

#endif