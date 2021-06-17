#include <stdio.h>

#include "TEClass.h"

class base1 {
public:
    int fun1();
};

int base1::fun1() {
    printf("base2::fun1\n");
    return 0x00;
}

//

class base2 {
public:
    int fun1();
};

int base2::fun1() {
    printf("base2::fun1\n");
    return 0x00;
}

//

class child : public base1, base2 {
public:
    int fun2();
    int fun1();
};

int child::fun2() {
    printf("child::fun2\n");
    return 0x00;
}

int child::fun1() {
    printf("child::fun1\n");
    return 0x00;
}

//int main() {
//    child ch;
//    ch.base1::fun1();
//    ch.fun1();
////
//    return 0x00;
//}