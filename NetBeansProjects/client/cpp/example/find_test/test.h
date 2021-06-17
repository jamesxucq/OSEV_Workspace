#ifndef TEST_H
#define TEST_H 

#include "osev_clie_cpp.h" 

namespace xxx {

    class test {
    public: // class meta 
        static class OSVBase meta_obje;
        static char *serialize(char *data, class test *obje);
        static char *deserialize(class test *obje, char *data);
        static const int seri_length;
    public:
        osv_oid_t obje_id;
        int xx;
        int ax;
        int cx;
    public: // construct 
        test();
    public:
        int Create(int aa);
        int Create(int aa, int bb);
        int tst(int yy);
    };
}

#endif /* TEST_H */ 

