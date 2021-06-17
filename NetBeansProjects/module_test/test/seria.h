#ifndef TEST_H
#define TEST_H 

#include "osev_clie_cpp.h" 

namespace xxx {

    class test {
    public:
        int xx;
        int ax;
        int cx;
        int creat_test(int aa);
        int creat_test(int aa, int bb);
        int tst(int yy);
    };

    class _test_meta_ : public OSVBase {
    public:
        int serialize(char *data, class test &obje);
        char *deserialize(class test &obje, char *data);
        int seri_length();
    };
    extern class _test_meta_ _test_sobje_;
}

#endif /* TEST_H */ 




