#include <string.h> 
#include "test.h" 
using namespace xxx;
namespace xxx {
#pragma pack(1) 

struct _test_ {
        osv_oid_t obje_id;
        int xx;
        int ax;
        int cx;
    };
#pragma pack(0) 
}
const int test::seri_length = sizeof (struct _test_);

char *test::serialize(char *data, class test *obje) {
    memcpy(&((struct _test_ *) data)->obje_id, &obje->obje_id, sizeof (osv_oid_t));
    ((struct _test_ *) data)->xx = obje->xx;
    ((struct _test_ *) data)->ax = obje->ax;
    ((struct _test_ *) data)->cx = obje->cx;
    return data + sizeof (struct _test_);
}

char *test::deserialize(class test *obje, char *data) {
    memcpy(&obje->obje_id, &((struct _test_ *) data)->obje_id, sizeof (osv_oid_t));
    obje->xx = ((struct _test_ *) data)->xx;
    obje->ax = ((struct _test_ *) data)->ax;
    obje->cx = ((struct _test_ *) data)->cx;
    return data + sizeof (struct _test_);
}

test::test() {
}

int test::Create(int aa) {
    creat_objeid_obj(&this->obje_id);
    this->xx = aa;
    return 0x00;
}

int test::Create(int aa, int bb) {
    creat_objeid_obj(&this->obje_id);
    this->xx = bb;
    this->ax = aa;
    return 0x00;
}

int test::tst(int yy) {
    this->xx = yy;
    return 0x00;
}
