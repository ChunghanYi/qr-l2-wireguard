#ifndef PQCLEAN_KYBER768_CLEAN_VERIFY_H
#define PQCLEAN_KYBER768_CLEAN_VERIFY_H
#include "params.h"
#include <linux/types.h>

int PQCLEAN_KYBER768_CLEAN_verify(const uint8_t *a, const uint8_t *b, size_t len);

void PQCLEAN_KYBER768_CLEAN_cmov(uint8_t *r, const uint8_t *x, size_t len, uint8_t b);

#endif
