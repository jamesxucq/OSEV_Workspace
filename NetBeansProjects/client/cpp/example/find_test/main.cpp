
/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2017年9月8日, 上午9:22
 */

#include <cstdlib>

#include <vector>
using std::vector;

using namespace std;

/*
 * 
 */

#include "test.h"
#include "osev_clie_cpp.h"
//

int main(int argc, char** argv) {
    //
    OSEVClient::Initial();
    //
    OSEVClient TestClie("test", "123456", "10.0.0.103", 8848);
    //
    OSEVConne TestConne;
    if (TestClie.getOSEVConne(TestConne, "xxx")) {
        printf("OSEVConne getOSEVConne error.\n");
        return -1;
    }
    //
    OSEVContain TestConta;
    if (TestConne.getContain(TestConta, "tvtv")) {
        printf("OSEVContain getContain error.\n");
        return -1;
    }
    //
    //    printf("OSEVContain Find start.\n");
    //    vector <class xxx::test *> FindVec;
    //    string PrediStri = "";
    //    if (TestConta.Find(FindVec, PrediStri)) {
    //        printf("OSEVContain Find error.\n");
    //        return -1;
    //    }
    //    //
    //    printf("OSEVContain Find ok.\n");
    char temp[33];
    //    vector <class xxx::test *>::iterator iter;
    //    for (iter = FindVec.begin(); iter != FindVec.end(); ++iter) {
    //        printf("|%s|%d|%d|%d|\n", oidstr(temp, &(*iter)->obje_id), (*iter)->xx, (*iter)->ax, (*iter)->cx);
    //    }
    //    OSEVContain::ClearVec(FindVec);
    //
    class xxx::test TestObje;
    TestObje.Create(12, 34);
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &TestObje.obje_id), TestObje.xx, TestObje.ax, TestObje.cx);
    TestConta.Inser(TestObje);
    TestObje.ax = 99;
    TestObje.cx = 22;
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &TestObje.obje_id), TestObje.xx, TestObje.ax, TestObje.cx);
    TestConta.Updat(TestObje);
    //
    OSEVClient::Cleanup();
    //
    return 0;
}

