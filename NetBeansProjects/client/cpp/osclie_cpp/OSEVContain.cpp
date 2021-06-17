
#include "OSEVContain.h"

OSEVContain::OSEVContain() {
}

OSEVContain::~OSEVContain() {
}

//

int OSEVContain::Create(osv_oid_t *oid, int conne_sock) {
    m_conne_sock = conne_sock;
    memcpy(&m_oid, oid, sizeof(osv_oid_t));
    return 0x00;
}

//
int OSEVContain::Drop(string &PrediStri) {
    printf("const_entry_drop\n");
    char *paras[0x02] = {NULL, NULL};
    if ("" != PrediStri) paras[0x00] = (char *) PrediStri.c_str();
printf("paras[0x00]:|%s|, paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    resp_data_t const_resp;
    if (clie_const_bzl(&const_resp, m_conne_sock, CONS_DROP, &m_oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}
