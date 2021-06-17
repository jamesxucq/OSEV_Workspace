
#include <ctype.h>

#include "third_party.h"
#include "conoda.h"
#include "dyli_list.h"
#include "updat.h"

//
/*
 #pragma pack(1) 
struct _test_ { 
osv_oid_t obje_oid; 
int xx; 
int ax; 
int cx; 
};
#pragma pack() 
 */

//

int updat_entity_obje(riv_curso_t *curso, rive_ha *stora_ha, hand_data *handa, char *clasn, char **paras) {
    _LOG_DEBUG("cuo clasn:|%s| handa->ocuse_hm:%08X", clasn, handa->ocuse_hm);
    //
    dyli_data *dldap = (dyli_data *) action_value(clasn, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    /*
    struct _test_ *test = paras[0x00];
        char temp[33];
    printf("|%s|%d|%d|%d|\n", oidstr(temp, &test->obje_oid), test->xx, test->ax, test->cx);
     */
    dldap->bound(curso, paras[0x00]);
    return stora_ha->inser_curso(curso);
}