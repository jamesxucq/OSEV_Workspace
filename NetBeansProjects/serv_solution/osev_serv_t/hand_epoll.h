#ifndef HAND_EPOLL_H
#define HAND_EPOLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"
#include "epoll_serv.h"

    //
    extern int(*recv_initialize_tab[])(struct _event*);
    extern int(*send_initialize_tab[])(struct _event*);

#ifdef __cplusplus
}
#endif

#endif /* HAND_EPOLL_H */