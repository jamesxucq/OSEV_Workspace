
/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2017年12月27日, 上午9:22
 */

#include <cstdlib>
#include "ha_heap.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //
    struct handlerton hdt;
    class ha_heap haheap(&hdt, NULL);
    //
    TABLE table_arg;
    HA_CREATE_INFO create_info;
    haheap.create("hello", &table_arg, &create_info);
    //
    return 0;
}

