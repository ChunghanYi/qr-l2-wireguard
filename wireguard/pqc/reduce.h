#ifndef PQCLEAN_KYBER768_CLEAN_REDUCE_H
#define PQCLEAN_KYBER768_CLEAN_REDUCE_H
#include "params.h"
#include <linux/types.h>

#define MONT (-1044) // 2^16 mod q
#define QINV (-3327) // q^-1 mod 2^16

int16_t PQCLEAN_KYBER768_CLEAN_montgomery_reduce(int32_t a);

int16_t PQCLEAN_KYBER768_CLEAN_barrett_reduce(int16_t a);

#endif
