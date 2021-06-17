
/* 
 * File:   OSEVConne.h
 * Author: Administrator
 *
 * Created on 2017.9.6
 */

#ifndef OSEV_CONNE_H
#define OSEV_CONNE_H

#include "entry_utili.h"
#include "clie_bzl.h"

#include <string>
using namespace std;

#include <vector>
using std::vector;

//

class OSEVConne {
public:
    string m_osev_osdb;
    osv_oid_t m_oid;
    int m_conne_sock;
public:
    OSEVConne();
    virtual ~OSEVConne();
public:
    int getContain(class OSEVContain &ContaObje, const string &ContaName);
public:
    template <class T> int ContaInser(T &InserObje);
    template <class T> int ContaInser(vector <T *> &InserVec);
    template <class T> int ContaFind(vector <T *> &FindVec, string &PrediStri);
    template <class T> int ContaDrop(vector <T *> &DropVec);
};

//

template <class T> int OSEVConne::ContaInser(T &InserObje) {
    printf("const_entry_creat\n");
    char *paras[0x02] = {NULL, NULL};
    //
    osv_pstyl_t pstyl;
    if (-1 == para_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, this->m_conne_sock, CONS_CREAT, &this->m_oid, &pstyl)) {
        printf("    query creat error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVConne::ContaInser(vector <T *> &InserVec) {
    printf("const_entry_inser\n");
    char *paras[0x02] = {NULL, NULL};
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, this->m_conne_sock, CONS_INSER, &this->m_oid, &pstyl)) {
        printf("    query inser error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVConne::ContaFind(vector <T *> &FindVec, string &PrediStri) {
    printf("const_entry_find\n");
    char *paras[0x02] = {NULL, NULL};
    if ("" != PrediStri) paras[0x00] = PrediStri.c_str();
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, this->m_conne_sock, CONS_FIND, &this->m_oid, &pstyl)) {
        printf("    query find error!\n");
        return -1;
    }
    //
    if (DeseObjeVec(FindVec, &const_resp)) {
        printf("    dese find error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVConne::ContaDrop(vector <T *> &DropVec) {
    printf("const_entry_drop\n");
    char *paras[0x02] = {NULL, NULL};
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, this->m_conne_sock, CONS_DROP, &this->m_oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

#endif /* OSEV_CONNE_H */

