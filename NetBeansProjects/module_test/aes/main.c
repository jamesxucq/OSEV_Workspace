/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2018年2月22日, 上午9:23
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#include<stdio.h>  
#include "mbedtls/aes.h"  
#include "mbedtls/compat-1.3.h"  

int main() {
    mbedtls_aes_context aes_ctx;
    //密钥数值  
    unsigned char key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00};
    //明文空间  
    unsigned char plain[16] = "helloworld";
    //解密后明文的空间  
    unsigned char dec_plain[16] = {0};
    //密文空间  
    unsigned char cipher[16] = {0};
    mbedtls_aes_init(&aes_ctx);
    //设置加密密钥  
    mbedtls_aes_setkey_enc(&aes_ctx, key, 128);
    printf("\n*********** 1:|%s|\n", plain);
    mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_ENCRYPT, plain, cipher);
    printf("\n*********** 2:|%s|\n", cipher);
    //设置解密密钥  
    mbedtls_aes_setkey_dec(&aes_ctx, key, 128);
    mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT, cipher, dec_plain);
    printf("\n*********** 3:|%s|\n", dec_plain);
    mbedtls_aes_free(&aes_ctx);
    // system("pause");
}

