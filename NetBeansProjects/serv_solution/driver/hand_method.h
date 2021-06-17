
#ifndef HAND_METHOD_H
#define HAND_METHOD_H

#include "requ_conne.h"
#include "requ_resp.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hand_reques(int conne_sock, requ_data_t *req_dat);
    int hand_respon(resp_data_t *res_dat, int conne_sock, requ_data_t *req_dat);

#ifdef __cplusplus
}
#endif

#endif /* HAND_METHOD_H */

