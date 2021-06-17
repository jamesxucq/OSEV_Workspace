
#ifndef OSCO_SOCKS_H
#define OSCO_SOCKS_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "commo_header.h"
#include "clie_macro.h"

    //
    int osco_connect(serv_addr *saddr);
    void osco_close(int conne_sock);
#define osco_close(conne_sock) close(conne_sock)

    //
    int send_receive(char *recv_buffer, char *send_buffer, int slen, int conne_sock);
    int osco_send(char *send_buffer, int slen, int conne_sock);
    int receive(char *recv_buffer, int conne_sock);

#ifdef __cplusplus
}
#endif

#endif /* OSCO_SOCKS_H */

