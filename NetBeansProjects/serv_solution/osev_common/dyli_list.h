
/* 
 * File:   dyli_list.h
 * Author: James Xu
 *
 * Created on 2017.1.10, PM 2:12
 */

#ifndef DYLI_LIST_H
#define DYLI_LIST_H

#include "utility/action_hmap.h"
#include "commo_macro.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct dyli_hand {
        char lib_path[MAX_PATH];
        void *handle;
        int refer_inde;
        struct dyli_hand *next;
    };

    //

    typedef struct {
        char clasn[CLASS_LENGTH];
        void *lib_hand;
        int data_size;
        void (*bound)(void *, void *);
        void (*solve)(void *, void *);
    } dyli_data;

    typedef void (*parse_rive)(void *, void *);

        /*
     static const struct vcha_node types_value_tab[] = {
        // extend
        {"short", 'h'},
        {"int", 'i'},
        {"uint", 'I'},
        {"long", 'l'},
        {"long long", 'q'},
        // base
        {"int8", 'b'},
        {"uint8", 'B'},
        {"int16", 'h'},
        {"uint16", 'H'},
        {"int32", 'i'},
        {"uint32", 'I'},
        {"int64", 'q'},
        {"uint64", 'Q'},
        {"byte", 's'},
        {"char", 'S'},
        //
        {NULL, 'x'}
    };
     */

    typedef union {
        void (*meth_void)(void *);
        char (*meth_char)(void *);
        unsigned char (*meth_ucha)(void *);
        short (*meth_shor)(void *);
        unsigned short (*meth_usho)(void *);
        int (*meth_int)(void *);
        unsigned int (*meth_uint)(void *);
        long (*meth_long)(void *);
        unsigned long (*meth_ulong)(void *);
        long long (*meth_llong)(void *);
        unsigned long long (*meth_ullong)(void *);
        char* (*meth_chap)(void *);
    } metho_user;

    typedef enum {
        rtyp_void,
        rtyp_char,
        rtyp_ucha,
        rtyp_shor,
        rtyp_usho,
        rtyp_int,
        rtyp_uint,
        rtyp_long,
        rtyp_ulon,
        rtyp_llon,
        rtyp_ullo,
        rtyp_chap
    } caller_type;

    //

    typedef struct {
        char handn[METH_LENGTH];
        void *lib_hand;
        dyli_data *dldat;
        //
        int (*parser)(char **);
        metho_user method;
        caller_type retype;
    } dyli_meth;

    //
    struct dyli_hand *new_dyha();
    void free_dyha(struct dyli_hand *dyha);
    //
    struct dyli_hand *open_dyhand(struct dyli_hand **dylsth, char *lib_path);
    void close_dyhand(struct dyli_hand **dylsth, void *lib_hand);
    inline void dyhand_dele(struct dyli_hand *dyha);
    //
    dyli_meth *new_dyme();
    void free_dyme(void *dyme);
    //
    dyli_data *new_dyda();
    void free_dyda(void *dyda);
    //

#ifdef __cplusplus
}
#endif

#endif /* DYLI_LIST_H */

