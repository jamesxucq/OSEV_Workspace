
/* 
 * File:   ivk_list.h
 * Author: James Xu
 *
 * Created on 2016.12.21, AM 10:57
 */

#ifndef IVK_LIST_H
#define IVK_LIST_H

#include "commo_macro.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct ivk_list {
        char meth_name[METH_NAME_LEN];
        char package_name[PACKAGE_LEN];
        void *meth_funcer;
        struct ivk_list *next;
    };
//
struct ivk_list *appe_ivklist_new(struct ivk_list **ivklsth);
inline void ivklist_dele(struct ivk_list *ivklist);


#ifdef __cplusplus
}
#endif

#endif /* IVK_LIST_H */

