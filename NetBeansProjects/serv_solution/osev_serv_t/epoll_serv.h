#ifndef EPOLL_SERV_H_
#define EPOLL_SERV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "commo_header.h"

#include "parse_conf.h"
#include "evd_list.h"
#include "event.h"

    //

    struct event_data {
        int sockfd;
        int evctrl; // 0:data 1:ctrl
        BYTE *buffer; // recv data buffer
        int rsleng;
        //
        int evloop;
        long last_active; // last active time
        //
        int evstat;
        struct _event *bev;
        int sleng;
    };
    //
#define CREATE_SRECVBUF(SRE_BUFF) \
    SRE_BUFF = (BYTE *) malloc(EVD_SOCKET_BUFF); \
    if(!SRE_BUFF) return ERR_FAULT; \
    memset(SRE_BUFF, '\0', EVD_SOCKET_BUFF);

#define DESTROY_SRECVBUF(SRE_BUFF) \
    if(SRE_BUFF) return free(SRE_BUFF); \
    SRE_BUFF = NULL;
    //
    int epoll_server(struct serv_config *config);
    int init_event_data(struct event_data *evds, int max_events);

#ifdef __cplusplus
}
#endif

#endif /* EPOLL_SERV_H_ */
