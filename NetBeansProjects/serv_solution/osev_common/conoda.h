
/* 
 * File:   conoda.h
 * Author: James Xu
 *
 * Created on 2017.1.11, PM 2:21
 */

#ifndef CONODA_H
#define CONODA_H

#include "commo_macro.h"
#include "osev_struct.h"
#include "hash_table_ex.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct cono_list {
        char *_osdb_;
        osv_oid_t *_oid_;
        conoda cono_valu;
        struct cono_list *next;
    };

    //
    extern struct cono_list *_conta_list_;

    //
    struct cono_list *appe_clist_new(struct cono_list **clsth);
    inline void clist_dele(struct cono_list *clist);
    conoda *find_conto_osdb(struct cono_list *clist, char *osdb);

    //
    struct cono_list *find_clstn(struct cono_list *clist, char *osdb);
    struct cono_list *find_clsto(struct cono_list *clist, osv_oid_t *oid);
    void close_clist(struct cono_list **clsth, struct cono_list *clist);

    //
#define ODATA_BACKET_SIZE      0x1000  // 4K
#define CONTA_BACKET_SIZE      512

#ifdef __cplusplus
}
#endif

#endif /* CONODA_H */

