/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2018年2月6日, 上午9:13
 */

#include <stdio.h>
#include <stdlib.h>

#include "imemo.h"

//

struct rivtest {
    int a;
    int b;
    int c;
};

//

int32 riv_each(ime_live *pliv) {
    struct rivtest *ldata;
    //
    struct imem_list *imem_data = pliv->elist;
    for (; imem_data; imem_data = imem_data->next) {
        ldata = (struct rivtest *) imem_data->idata;
        printf("einde:%u ldata:%d\n", imem_data->einde, ldata->a);
    }
}

/*
 * 
 */
int test1() {
    ime_live iliv;
    ime_live *pliv = &iliv;
    //
    ILIVE_INITI_POINT(pliv, sizeof (struct rivtest), "./test.rdb")

            //
    if (ime_create(pliv)) {
        printf("ime_create error.\n");
        return -1;
    }

    //

    if (ime_initial(pliv)) {
        printf("ime_initial error.\n");
        return -1;
    }

    //
    struct rivtest rtest;
    rtest.a = 101;
    printf("ime_insert ---------\n");
    if (ime_insert(pliv, (char *) &rtest)) {
        printf("ime_insert error.\n");
        return -1;
    }
    rtest.a = 102;
    ime_insert(pliv, (char *) &rtest);
    rtest.a = 103;
    ime_insert(pliv, (char *) &rtest);
    rtest.a = 102;
    ime_insert(pliv, (char *) &rtest);
    rtest.a = 103;
    ime_insert(pliv, (char *) &rtest);
    riv_each(pliv);
    printf("--------- ime_echo ---------\n");
    ime_echo(pliv);
    //
    printf("ime_remove ---------\n");
    if (-1 == ime_remove(pliv, (char *)&rtest)){
        printf("ime_remove error.\n");
        return -1;
    }
    ime_remove(pliv, pliv->elist->idata);
    printf("--------- ime_echo ---------\n");
    ime_echo(pliv);
    ime_remove(pliv, pliv->elist->idata);
    riv_each(pliv);
    printf("--------- ime_echo ---------\n");
    ime_echo(pliv);
    //
    printf("ime_insert ---------\n");
    rtest.a = 100;
    ime_insert(pliv, (char *) &rtest);
    riv_each(pliv);
    //
    printf("--------- ime_echo ---------\n");
    ime_echo(pliv);

    printf("ime_final ---------\n");
    if (ime_final(pliv)) {
        printf("ime_final error.\n");
        return -1;
    }

    //    //
/*
    if (ime_destroy(pliv)) {
        printf("ime_destroy error.\n");
        return -1;
    }
*/
    //
    // printf("%d %d\n", sizeof(uint32), sizeof(uint64));
    // printf("%u\n", INVA_INDE_VALU);

    return 0x00;
}

int test2() {
    ime_live iliv;
    ime_live *pliv = &iliv;
    //
    ILIVE_INITI_POINT(pliv, sizeof (struct rivtest), "./test.rdb")
            //
    if (ime_initial(pliv)) {
        printf("ime_initial error.\n");
        return -1;
    }
    //
    printf("---------\n");
    ime_echo(pliv);
    printf("---------\n");
    riv_each(pliv);
    printf("---------\n");
    if (ime_final(pliv)) {
        printf("ime_final error.\n");
        return -1;
    }
    //
    return 0x00;
}

int main(int argc, char** argv) {
    test1();
    // test2();
    //
    return (EXIT_SUCCESS);
}


