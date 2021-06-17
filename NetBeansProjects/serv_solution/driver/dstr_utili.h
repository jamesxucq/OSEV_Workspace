
#ifndef DSTR_UTILI_H
#define DSTR_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clie_macro.h"
#include "requ_conne.h"
#include "osco_socks.h"

    //
    int creat_authe_ine(struct authe_ine *auth, char *usern, char *paswd);

    //

    typedef struct {
        char pstyl_str[LARGE_TEXT_SIZE];
        int colen;
    } osv_pstyl_t;

    //
    int ston_pstyl(osv_pstyl_t *pscon, char **paras);
    int dist_pstyl(osv_pstyl_t *pscon, char **paras);

    //
    int const_invok_pstyl(osv_pstyl_t *pscon, char **paras);
    int invok_list_pstyl(osv_pstyl_t *pscon, char **paras);
    int colle_list_pstyl(osv_pstyl_t *pscon, char **paras);

    //
#define LIST_CLAS_OBJID 0x0001
#define LIST_CLAS_ATTRIB 0x0002
#define LIST_CLAS_INHERIT 0x0004
#define LIST_CLAS_CONTEN 0x0008
    unsigned int invo_list_type(char *invo_type);

    //

    
#ifdef __cplusplus
}
#endif

#endif /* DSTR_UTILI_H */

