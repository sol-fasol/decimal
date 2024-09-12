#ifndef S21_GETSET_H

#define S21_GETSET_H

#include <stdint.h>

#include "../s21_decimal.h"

#define DEC_SIGN_MASK 0x80000000
#define DEC_SCALE_MASK 0x00FF0000

#define DEC_SCALE_SHIFT 16
#define DEC_BIT_SHIFT 32

typedef uint32_t t_u32;
typedef uint64_t t_u64;

void s21_set32(void *dec, int i, t_u32 val);
void s21_set64(void *dec, int i, t_u64 val);
void s21_dec_set_l32_h64(void *dec, t_u32 low, t_u64 high);
void s21_dec_set_l64_h32(void *dec, t_u64 low, t_u32 high);
int s21_dec_set_u32_scale(s21_decimal *dec, t_u64 mant, int scale);
void s21_dec_setscale(void *d, int scale);
void s21_dec_setflags(void *d, t_u32 flags);
void s21_dec_negate(void *d);
void s21_buf_cpy(const void *src, void *dst, int n);
void s21_swap(void *p1, void *p2);

t_u32 s21_get32(void *dec, int i);
t_u64 s21_get64(void *dec, int i);
t_u32 s21_dec_getflags(void *arg);
int s21_dec_getscale(void *d);
int s21_get_high_bit(const void *d, int end);
int s21_dec_getsign(void *d);
int s21_dec_iszero(const void *d);
int s21_dec_isvalid(void *arg);
t_u32 s21_xor_signs(void *d1, void *d2);

#endif