#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1) 

typedef struct {
    unsigned int osev_unique;
    unsigned long long stoid;
} osv_oid_i;
#pragma pack() 
int _test_test_ii_retype_ = 5;

static int aa;
static int bb;

void _parse_test_test_ii_(char **paras) {
    char **valu = paras;
    aa = (int) ((*valu)[0x01]);
    ++valu;
    bb = (int) ((*valu)[0x01]);
}
#pragma pack(1)

struct test {
    osv_oid_i obje_oid;
    int xx;
    int ax;
    int cx;
};
#pragma pack() 

int test_test_ii(struct test *this) {
    this->xx = bb;
    this->ax = aa;
    return 0x00;
}

