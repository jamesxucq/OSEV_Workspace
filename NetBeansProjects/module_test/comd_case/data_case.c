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
