
/* 
 * File:   OSEVContain.h
 * Author: Administrator
 *
 * Created on 2017.9.6
 */

#ifndef OSEV_CONTAIN_H
#define OSEV_CONTAIN_H

#include "osev_common/commo_header.h"
#include "stri_utili.h"
#include "entry_utili.h"
#include "clie_bzl.h"

#include <string>
using namespace std;

#include <vector>
using std::vector;

//

class OSEVContain {
private:
    osv_oid_t m_oid;
    int m_conne_sock;
public:
    OSEVContain();
    virtual ~OSEVContain();
public:
    int Create(osv_oid_t *oid, int conne_sock);
public:
    template <class T> int Creat(T &CreatObje);
    template <class T> int Creat(vector <T *> &CreatVec);
    //
    template <class T> int Drop(T &DropObje); // test pass
    template <class T> int Drop(vector <T *> &DropVec);
    int Drop(string &PrediStri);
    //
    template <class T> int Updat(T &UpdatObje); // pass
    template <class T> int Updat(vector <T *> &UpdatVec);
    //
    template <class T> int Inser(T &InserObje); // pass
    template <class T> int Inser(vector <T *> &InserVec);
    //
    template <class T> int Find(T &FindObje, string &PrediStri); // test pass
    template <class T> int Find(vector <T *> &FindVec, string &PrediStri); // test pass
public:
    template <class T> static void ClearVec(vector <T *> &CleaVec);
};

//

template <class T> int OSEVContain::Drop(T &DropObje) {
    printf("const_entry_drop\n");
    char *paras[0x02] = {NULL, NULL};
    char oid_stri[OID_LINE_LEN];
    paras[0x00] = oid_stri;
    oidstr(oid_stri, &DropObje.obje_id);
    printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_DROP, &m_oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVContain::Drop(vector <T *> &DropVec) {
    printf("const_entry_drop\n");
    char *paras[0x02] = {NULL, NULL};
    char oid_stri[OID_LINE_LEN];
    paras[0x00] = oid_stri;
    //
    class vector <T *>::iterator iter;
    for (iter = DropVec.begin(); iter != DropVec.end(); ++iter) {
        oidstr(oid_stri, &(*iter)->obje_id);
        printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
        osv_pstyl_t pstyl;
        if (-1 == line_pstyl(&pstyl, paras)) return -1;
        //
        resp_data_t const_resp;
        if (clie_const_bzl(&const_resp, m_conne_sock, CONS_DROP, &m_oid, &pstyl)) {
            printf("    query drop error!\n");
            return -1;
        }
    }
    //
    return 0x00;
}

//

template <class T> int OSEVContain::Updat(T &UpdatObje) {
    printf("const_entry_updat\n");
    char *paras[0x02] = {NULL, NULL};
    char obje_cont[OBJE_CONTE_LEN];
    paras[0x00] = obje_cont;
    SeriObje(obje_cont, UpdatObje);
    printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    osv_pstyl_t pstyl;
    if (-1 == bina_pstyl(&pstyl, paras, T::seri_length)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_UPDAT, &m_oid, &pstyl)) {
        printf("    query update error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVContain::Inser(T &InserObje) {
    printf("const_entry_inser\n");
    char *paras[0x02] = {NULL, NULL};
    char obje_cont[OBJE_CONTE_LEN];
    paras[0x00] = obje_cont;
    SeriObje(obje_cont, InserObje);
printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
//
    osv_pstyl_t pstyl;
    if (-1 == bina_pstyl(&pstyl, paras, T::seri_length)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_INSER, &m_oid, &pstyl)) {
        printf("    query inser error!\n");
        return -1;
    }
    //
    return 0x00;
}

template <class T> int OSEVContain::Inser(vector <T *> &InserVec) {
    printf("const_entry_inser\n");
    char *paras[0x02] = {NULL, NULL};
printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
//
    osv_pstyl_t pstyl;
    if (-1 == bina_pstyl(&pstyl, paras, T::seri_length())) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_INSER, &m_oid, &pstyl)) {
        printf("    query inser error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

template <class T> int OSEVContain::Find(T &FindObje, string &PrediStri) {
    printf("const_entry_find\n");
    char *paras[0x02] = {NULL, NULL};
    if ("" != PrediStri) paras[0x00] = (char *) PrediStri.c_str();
    // printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_FIND, &m_oid, &pstyl)) {
        printf("    query find error!\n");
        return -1;
    }
    DeseObje(FindObje, &const_resp);
    //
    return 0x00;
}

template <class T> int OSEVContain::Find(vector <T *> &FindVec, string &PrediStri) {
    printf("const_entry_find\n");
    char *paras[0x02] = {NULL, NULL};
    if ("" != PrediStri) paras[0x00] = (char *) PrediStri.c_str();
    // printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_FIND, &m_oid, &pstyl)) {
        printf("    query find error!\n");
        return -1;
    }
    DeseObjeVec(FindVec, &const_resp);
    //
    return 0x00;
}

//

template <class T> void OSEVContain::ClearVec(vector <T *> &CleaVec) {
    class vector <T *>::iterator iter;
    for (iter = CleaVec.begin(); iter != CleaVec.end(); ++iter)
        delete (*iter);
    CleaVec.clear();
}

//

#endif /* OSEV_CONTAIN_H */

