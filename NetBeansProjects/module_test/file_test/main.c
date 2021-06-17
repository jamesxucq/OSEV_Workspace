/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: james
 *
 * Created on 2021年4月22日, 下午4:39
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *fp1 = fopen("./ffff", "wb+");
    FILE *fp2 = fp1;
    printf("%llu\n", *fp1);
        printf("%llu\n", *fp2);
    // fclose(fp2);
    fputc('c', fp1);
    fclose(fp1);
    //
    return (EXIT_SUCCESS);
}

