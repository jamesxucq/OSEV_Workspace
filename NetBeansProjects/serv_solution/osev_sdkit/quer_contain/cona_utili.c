

#include "cona_utili.h"
#include "cona_list.h"
#include "osev_struct.h"

//
int inser_conta_list(cont_data *conda, cont_list *colist) {
    cont_list *colitmp = colist;
    while (colitmp) {
_LOG_DEBUG("inser_conta_list:%s", colitmp->conta->cont_name);
        action_insert(colitmp->conta->cont_name, (void *) colitmp->conta, conda->contn_hm);
        cache_insert(&colitmp->conta->oid, (void *) colitmp->conta, conda->conto_hm);
        colitmp = colitmp->next;
    }
//
    return 0x00;
}