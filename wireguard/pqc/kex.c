/*
 * kex.c - Kyber Authenticated Kex Exchange from the crystals/kyber/ref/kex.c file
 */

#include "kex.h"
#include "kem.h"
#include "symmetric.h"

void kex_uake_initA(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb) {
	PQCLEAN_KYBER768_CLEAN_crypto_kem_keypair(send, sk);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_enc(send+PQCLEAN_KYBER768_CLEAN_CRYPTO_PUBLICKEYBYTES, tk, pkb);
}

void kex_uake_sharedB(uint8_t *send, uint8_t *k, const uint8_t *recv, const uint8_t *skb) {
	uint8_t buf[2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES];

	PQCLEAN_KYBER768_CLEAN_crypto_kem_enc(send, buf, recv);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_dec(buf+PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES,
			recv+PQCLEAN_KYBER768_CLEAN_CRYPTO_PUBLICKEYBYTES, skb);
	kdf(k, buf, 2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES);
}

void kex_uake_sharedA(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk) {
	unsigned int i;
	uint8_t buf[2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES];

	PQCLEAN_KYBER768_CLEAN_crypto_kem_dec(buf, recv, sk);
	for(i=0;i<PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES;i++)
		buf[i+PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES] = tk[i];
	kdf(k, buf, 2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES);
}

void kex_ake_initA(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb) {
	PQCLEAN_KYBER768_CLEAN_crypto_kem_keypair(send, sk);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_enc(send+PQCLEAN_KYBER768_CLEAN_CRYPTO_PUBLICKEYBYTES, tk, pkb);
}

void kex_ake_sharedB(uint8_t *send, uint8_t *k, const uint8_t* recv, const uint8_t *skb, const uint8_t *pka) {
	uint8_t buf[3*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES];

	PQCLEAN_KYBER768_CLEAN_crypto_kem_enc(send, buf, recv);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_enc(send+PQCLEAN_KYBER768_CLEAN_CRYPTO_CIPHERTEXTBYTES,
			buf+PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES, pka);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_dec(buf+2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES,
			recv+PQCLEAN_KYBER768_CLEAN_CRYPTO_PUBLICKEYBYTES, skb);
	kdf(k, buf, 3*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES);
}

void kex_ake_sharedA(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk,
		const uint8_t *ska) {
	unsigned int i;
	uint8_t buf[3*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES];

	PQCLEAN_KYBER768_CLEAN_crypto_kem_dec(buf, recv, sk);
	PQCLEAN_KYBER768_CLEAN_crypto_kem_dec(buf+PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES,
			recv+PQCLEAN_KYBER768_CLEAN_CRYPTO_CIPHERTEXTBYTES, ska);
	for(i=0;i<PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES;i++)
		buf[i+2*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES] = tk[i];
	kdf(k, buf, 3*PQCLEAN_KYBER768_CLEAN_CRYPTO_BYTES);
}
