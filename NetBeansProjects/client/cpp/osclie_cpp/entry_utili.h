
/* 
 * File:   entry_utili.h
 * Author: Administrator
 *
 * Created on 2017.9.6
 */

#ifndef ENTRY_UTILI_H
#define ENTRY_UTILI_H

//
#include <string>
using namespace std;

#include <vector>
using std::vector;

//
#include "requ_resp.h"

//
template <class T> void DeseObje(T &DesObj, resp_data_t *obje_resp) {
    T::deserialize(&DesObj, obje_resp->res_data);
}


template <class T> void DeseObjeVec(vector <T *> &DeseVec, resp_data_t *obje_resp) {
    char *parse_end = obje_resp->res_data + obje_resp->resp_len;
            char *parse_tok = obje_resp->res_data;
            T *eobje;
    while (parse_tok < parse_end) {
        eobje = new T();
                parse_tok = T::deserialize(eobje, parse_tok);
                DeseVec.push_back(eobje);
    }
}

//

template <class T> void SeriObje(char *obje_data, T &SerObj) {
    T::serialize(obje_data, &SerObj);
}


template <class T> void SeriObjeVec(vector <T *> &SeriVec, resp_data_t *obje_resp) {
    char *parse_end = obje_resp->res_data + obje_resp->resp_len;
            char *parse_tok = obje_resp->res_data;
            T *eobje;
    while (parse_tok < parse_end) {
        eobje = new T();
                parse_tok = T::deserialize(eobje, parse_tok);
                SeriVec.push_back(eobje);
    }
}


//

#endif /* ENTRY_UTILI_H */

