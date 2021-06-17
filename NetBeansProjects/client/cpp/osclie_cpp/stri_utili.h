
#ifndef STRI_UTILI_H
#define STRI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "osev_common/commo_header.h"
#include "clie_macro.h"
#include "osco_socks.h"

    //
    int creat_authe(struct authe_ine *auth, char *user, char *pwd);

    //

    typedef struct {
        char pstyl_str[LARGE_TEXT_SIZE];
        int colen;
    } osv_pstyl_t;

    //
    int line_pstyl(osv_pstyl_t *pscon, char **paras);
    int para_pstyl(osv_pstyl_t *pscon, char **paras);
    int bina_pstyl(osv_pstyl_t *pscon, char **paras, int seri_length);

    //
    int const_invok_pstyl(osv_pstyl_t *pscon, char **paras);
    int invok_echo_pstyl(osv_pstyl_t *pscon, char **paras);

    //
#define ECHO_CLAS_ATTRIB 0x0001
#define ECHO_CLAS_INHERIT 0x0002
#define ECHO_CLAS_CONTEN 0x0004
    unsigned int invo_echo_type(char *invo_etype);


#ifdef __cplusplus
}
#endif

#endif /* STRI_UTILI_H */

