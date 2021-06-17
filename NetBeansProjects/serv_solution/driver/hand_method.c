
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "requ_conne.h"
#include "resp_conne.h"
#include "osco_socks.h"
#include "clie_macro.h"
#include "hand_method.h"
#include "osev_clie.h"

//

int hand_reques(int conne_sock, requ_data_t *req_dat) {
    char revbuf[CONNE_DATA_LEN];
    memset(revbuf, '\0', CONNE_DATA_LEN);
    if (send_receive(revbuf, (char*) req_dat->req_data, req_dat->requ_len, conne_sock) == -1) {
        printf("    handle send recv execep!\n");
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
        printf("    method send recv execep!\n");
        return -1;
    }
    printf("recvlen:%d\n", recvlen);
    //
    resp_tyle_t resp_head;
    memcpy(&resp_head, revbuf, sizeof (resp_tyle_t));
    memcpy(res_dat->res_data, revbuf + sizeof (resp_tyle_t), recvlen - sizeof (resp_tyle_t));
    printf("    method resp_head.length:%d\n", resp_head.length);
    int recv_total = recvlen - sizeof (resp_tyle_t);
    // printf("recv_total:%d\n", recv_total);
    while (resp_head.length != recv_total) {
        recvlen = receive(revbuf, conne_sock);
        printf("recvlen:%d\n", recvlen);
        if (-1 == recvlen) {
            printf("    method send recv execep!\n");
            return -1;
        }
        memcpy(res_dat->res_data + recv_total, revbuf, recvlen);
        recv_total += recvlen;
    }
    res_dat->resp_len = resp_head.length;
    //
    printf("    method resp_head.status:%X\n", resp_head.status);
    return resp_head.status;
}