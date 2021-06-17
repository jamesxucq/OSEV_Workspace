#ifndef _EVD_LIST_H_
#define _EVD_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"

    struct levd_list {
        struct levd_list *prev, *next;
        struct event_data *evd;
    };

    struct evd_list {
        struct levd_list *active;
        struct levd_list *sleep;
        struct levd_list *chkpos;
    };

    //
    //
#include "epoll_serv.h"
    int init_evd_list(struct evd_list *elist, struct event_data *evds, int events_tatol);
    void dele_evd_list(struct evd_list *elist);

    struct levd_list *get_levd_list(struct evd_list *elist);
    struct levd_list *set_levd_list(struct evd_list *elist, struct event_data *evd);

#ifdef __cplusplus
}
#endif

#endif /* _EVD_LIST_H_ */


