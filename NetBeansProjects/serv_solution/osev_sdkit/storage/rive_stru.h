
/* 
 * File:   rive_stru.h
 * Author: James Xu
 *
 * Created on 2018.3.12, PM 2:27
 */

#ifndef RIVE_STRU_H
#define RIVE_STRU_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    #include "wiredtiger/wiredtiger.h"

    //
    typedef void riv_conne_t;
    typedef void riv_sessi_t;
    typedef void riv_curso_t;
    // typedef WT_CURSOR riv_curso_t;
    typedef WT_ITEM riv_item;


    //

    typedef struct seio_list_t {
        riv_sessi_t *seion;
        struct seio_list_t *next;
    } seio_list;

    //
#define RIV_NOVWT_CONF    "overwrite=false"
#define RIV_OVEWT_CONF    "overwrite=true" // by default

    //

    typedef struct {
        riv_conne_t *conne;
        seio_list *slist;
    } rive_conne;

    //

    typedef struct {
        char *storage_name;
        unsigned int storage_type;
        // connect
        int (*open_conne)(riv_conne_t **, char *, int);
        int (*close_conne)(riv_conne_t *);
        // session
        int (*open_sessi)(rive_conne *, riv_sessi_t **);
        int (*close_sessi)(riv_sessi_t *);
        int (*log_flush_sessi)(riv_sessi_t *);
        int (*begin_transa_sessi)(riv_sessi_t *);
        int (*commit_transa_sessi)(riv_sessi_t *);
        int (*reset_sessi)(riv_sessi_t *);
        // cursor
        int (*open_curso)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_table)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_group)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_index)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*close_curso)(riv_curso_t *);
        int (*inser_curso)(riv_curso_t *);
        int (*reset_curso)(riv_curso_t *);
        int (*next_curso)(riv_curso_t *);
        int (*prev_curso)(riv_curso_t *);
        int (*sear_curso)(riv_curso_t *);
        int (*searn_curso)(riv_curso_t *, int *);
        int (*update_curso)(riv_curso_t *);
        int (*remove_curso)(riv_curso_t *);
        int (*reconf_curso)(riv_curso_t *, char *);
        void (*set_key)(riv_curso_t *, unsigned long long);
        void (*set_value)(riv_curso_t *, void *);
        int (*get_key)(riv_curso_t *, void *);
        int (*get_value)(riv_curso_t *, void *);
        // contain
        int (*creat_conta)(riv_sessi_t *, char *, char *);
        int (*dorp_conta)(riv_sessi_t *, char *);
        int (*rename_conta)(riv_sessi_t *, char *, char *);
    } rive_ha;

    //
    /*
static rive_ha wtiger_ha = {
    WTIGER_ENAME,
    ENGINE_WTIGER,
    wt_open_conne,
    wt_close_conne,
    //
    wt_open_sess,
    wt_close_sess,
    wt_log_flush,
    wt_begin_transa_sess,
    wt_commit_transa_sess,
    wt_reset_sess,
    //
    wt_open_curs,
    wt_close_curs,
    wt_inser_curs,
    wt_reset_curs,
    wt_next_curs,
    wt_prev_curs,
    wt_sear_curs,
    wt_searn_curs,
    wt_update_curs,
    wt_remove_curs,
    wt_reconf_curs,
    set_key_wt,
    //
    wt_creat_tab,
    wt_dorp_tab,
    wt_rename_tab
};
     */

#ifdef __cplusplus
}
#endif

#endif /* RIVE_STRU_H */

