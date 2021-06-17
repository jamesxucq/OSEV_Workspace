/* 
 * File:   privi_cache.h
 * Author: David
 *
 * Created on: 2010-3-10
 */

#ifndef PRIVI_CACHE_H
#define PRIVI_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    // #include "shape/shape.h"

    //
#include "commo_header.h"
#include "hash_table_ex.h"
#include "stri_utili.h"
#include "liv_list.h"

    //

    list_data* new_ldata();
#define DELETE_LDATA(LDATA)     { if (ldata) free(ldata); LDATA = NULL; }
    void free_ldata(void* ldata);

    //
    extern actionmap *_ldata_hm_;
    extern cachemap *_ouser_hm_;
    extern cachemap *_cuser_hm_;

    //
    int creat_ouser_cache(cachemap *ouser_hm, struct liv_list *role_list, struct liv_list *ouse_list);
    int creat_cuser_cache(cachemap *cuser_hm, struct liv_list *role_list, struct liv_list *cuse_list);

    //
#define addi_user_cache(user_hm, user_dat) cache_insert(user_dat->user_name, user_dat, user_hm)
#define dele_user_cache(user_hm, user_dat) cache_remove(user_dat->user_name, user_hm)

    //
#define find_user_cache(user_hm, user_name) cache_value(user_name, user_hm)

    //

#ifdef __cplusplus
}
#endif

#endif /* PRIVI_CACHE_H */

