//
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiredtiger.h"
#include "wiredtiger_ext.h"
#pragma pack(1) 

typedef struct {
    unsigned int mach_unique;
    unsigned long long stoid;
} osv_oid_i;
#pragma pack() 
typedef WT_CURSOR riv_curso_t;
#pragma pack(1)

struct test {
    osv_oid_i obje_oid;
    int xx;
    int ax;
    int cx;
};
#pragma pack() 
struct test _test_sobj_;
int _test_size_ = sizeof (struct test);

void _bind_test_(riv_curso_t *curso, struct test *obje_data) {
    curso->set_key(curso, obje_data->obje_oid.stoid);
    curso->set_value(curso, obje_data->xx, obje_data->ax, obje_data->cx);
}

void _solve_test_(struct test *obje_data, riv_curso_t *curso) {
    curso->get_key(curso, &(obje_data->obje_oid.stoid));
    curso->get_value(curso, &obje_data->xx, &obje_data->ax, &obje_data->cx);
}
 */


//
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiredtiger.h"
#include "wiredtiger_ext.h"
#pragma pack(1) 

typedef struct {
    unsigned int osev_unique;
    unsigned long long stoid;
} osv_oid_i;
#pragma pack() 
typedef WT_CURSOR riv_curso_t;
#pragma pack(1)

struct {
    osv_oid_i obje_oid;
    uint type;
    char name[32];
    char array[128];
};
#pragma pack() 
struct __sobj_;
int __size_ = sizeof (struct);

void _bind__(riv_curso_t *curso, struct *obje_data) {
    curso->set_key(curso, obje_data->obje_oid.stoid);
    curso->set_value(curso, obje_data->type, obje_data->name, obje_data->array);
}

void _solve__(struct *obje_data, riv_curso_t *curso) {
    char *dat1, *dat2;
    curso->get_key(curso, &(obje_data->obje_oid.stoid));
    curso->get_value(curso, &obje_data->type, &dat1, &dat2);
    memcpy(obje_data->name, dat1, 32);
    memcpy(obje_data->array, dat2, 128);
}
*/
