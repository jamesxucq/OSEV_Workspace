
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osev_common/commo_header.h"
#include "osco_socks.h"
#include "hand_method.h"

//

int hand_reques(int conne_sock, requ_data_t *req_dat) {
    char revbuf[CONNE_DATA_LEN];
    memset(revbuf, '\0', CONNE_DATA_LEN);
    if (send_receive(revbuf, (char*) req_dat->req_data, req_dat->requ_len, conne_sock) == -1) {
        printf("    handle send recv exception!\n");
        return -1;
    }
    //
    resp_tyle_t *resp_head = (resp_tyle_t *) revbuf;
    printf("    handle resp_head->status:%d\n", resp_head->status);
    return resp_head->status;
}

int hand_respon(resp_data_t *res_dat, int conne_sock, requ_data_t *req_dat) {
    char revbuf[CONNE_DATA_LEN];
    memset(revbuf, '\0', CONNE_DATA_LEN);
    int recvlen = send_receive(revbuf, (char*) req_dat->req_data, req_dat->requ_len, conne_sock);
    if (-1 == recvlen) {
        printf("    method send recv exception!\n");
        return -1;
    }
    printf("recvlen:%d\n", recvlen);
    //
    resp_tyle_t resp_head;
    int recv_total;
    //
    memcpy(&resp_head, revbuf, sizeof (resp_tyle_t));
    memcpy(res_dat->res_data, revbuf + sizeof (resp_tyle_t), recvlen - sizeof (resp_tyle_t));
    recv_total = recvlen;
    while (sizeof (resp_tyle_t) + resp_head.length != recv_total) {
        recvlen = receive(revbuf, conne_sock);
        printf("recvlen:%d\n", recvlen);
        if (-1 == recvlen) {
            printf("    method send recv exception!\n");
            return -1;
        }
        memcpy(res_dat->res_data + recv_total, revbuf, recvlen);
        recv_total += recvlen;
    }
    res_dat->resp_len = resp_head.length;
    //
    printf("    method requ_head.status:%d\n", resp_head.status);
    return resp_head.status;
}