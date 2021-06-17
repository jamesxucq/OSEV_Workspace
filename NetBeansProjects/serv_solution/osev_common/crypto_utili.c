#include<stdio.h>  

#include "commo_macro.h"
#include "osev_macro.h"
#include "mbedtls/aes.h"  
#include "mbedtls/compat-1.3.h"  
#include "crypto_utili.h"
#include "stri_utili.h"


//
#define AUTH_MAGIC_STRI "emsaBJLdCi0v9a3D"

unsigned char *build_authen_key(unsigned char *ecb_key, char *user_salt) {
    char *passwd = AUTH_MAGIC_STRI;
    unsigned char *key = ecb_key;
    char *salt = user_salt;
    //
    int inde;
    for (inde = 0x00; KEY_LENGTH > inde; inde++) {
        key[0x00] = salt[0x00]^passwd[0x00];
        passwd++;
        salt++;
        key++;
    }
    //
    return ecb_key;
}

unsigned char *crypto_decode_ecb(unsigned char *plain, unsigned char *cipher, unsigned char *ecb_key) {
    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);
    //
    mbedtls_aes_setkey_dec(&aes_ctx, ecb_key, 128);
    mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT, cipher, plain);
    //
    mbedtls_aes_free(&aes_ctx);
    return plain;
}

//

unsigned char *crypto_encode_ecb(unsigned char *cipher, unsigned char *plain, unsigned char *ecb_key) {
    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);
    //    
    mbedtls_aes_setkey_enc(&aes_ctx, ecb_key, 128);
    mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_ENCRYPT, plain, cipher);
    //
    mbedtls_aes_free(&aes_ctx);
    return cipher;
}

//

void encode_salt_paswd(char *salt_paswd, char *salt, char *paswd) {
    char *last_str = lsncpy(salt_paswd, salt, SALT_LENGTH);
    lsncpy(last_str, paswd, PASWD_LENGTH);
}

void decode_salt_paswd(char *salt, char *paswd, char *salt_paswd) {
    lsncpy(salt, salt_paswd, SALT_LENGTH);
    lsncpy(paswd, salt_paswd + SALT_LENGTH, PASWD_LENGTH);
}