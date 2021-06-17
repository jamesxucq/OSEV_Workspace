
#include "clie_bzl.h"
#include "osev_common/commo_header.h"
#include "osco_socks.h"

#include "OSEVContain.h"
#include "OSEVConne.h"

//

OSEVConne::OSEVConne() {
}

OSEVConne::~OSEVConne() {
    clie_destroy_bzl(m_conne_sock, &m_oid);
    osco_close(m_conne_sock);
}

//

int OSEVConne::getContain(class OSEVContain &ContaObje, const string &ContaName) {
    osv_oid_t *obje_id = find_conta_bzl((char *)ContaName.c_str(), &m_oid, m_conne_sock);
    if (!obje_id) {
        printf("not find the conta.\n");
        return -1;
    }
    ContaObje.Create(obje_id, m_conne_sock);
    //
    return 0x00;
}


//

