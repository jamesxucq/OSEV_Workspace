#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//
#include "commo_macro.h"
#include "encoding.h"

//
char *random_salt(char *salt_value) {
    char rand_str[MIN_TEXT_LEN];
    char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    unsigned int last_seed;
    //
    if (!salt_value) return NULL;
    last_seed = time(NULL);
    int tatol;
    for (tatol = 0; tatol < 16; tatol++) {
        srand((unsigned int) last_seed);
        last_seed = rand();
        rand_str[tatol] = code_array[last_seed % 62];
    }
    rand_str[tatol] = '\0';
    strcpy(salt_value, rand_str);
    //
    return salt_value;
}
