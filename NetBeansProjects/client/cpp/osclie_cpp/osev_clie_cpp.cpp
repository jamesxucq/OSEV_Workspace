#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osev_common/commo_header.h"
#include "clie_bzl.h"
#include "osev_clie_cpp.h"
#include "osco_socks.h"

//

OSEVClient::OSEVClient(const string &UserName, const string &Password, const string &Address, int Port) {
    m_UserName = UserName;
    m_Password = Password;
    m_Address = Address;
    m_Port = Port;
}

OSEVClient::~OSEVClient() {
}

int OSEVClient::getOSEVConne(OSEVConne &ObjeConne, const string &BaseName) {
    printf("osev_clie_create\n");
    serv_addr saddr;
    struct authe_ine authe;
    char *paras[0x02] = {(char *) BaseName.c_str(), NULL};
    //
    creat_authe(&authe, (char *) m_UserName.c_str(), (char *) m_Password.c_str());
    strcpy(saddr.sin_addr, m_Address.c_str());
    saddr.sin_port = m_Port;
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    ObjeConne.m_osev_osdb = BaseName;
    ObjeConne.m_conne_sock = osco_connect(&saddr);
    if (-1 == ObjeConne.m_conne_sock) {
        osco_close(ObjeConne.m_conne_sock);
        printf("    osev connect error!\n");
        return -1;
    }
    //
    resp_data_t clie_resp;
    if (clie_create_bzl(&clie_resp, ObjeConne.m_conne_sock, &authe, &pstyl)) {
        osco_close(ObjeConne.m_conne_sock);
        printf("    osev osauth error!\n");
        return -1;
    }
    memcpy(&ObjeConne.m_oid, clie_resp.res_data, sizeof (osv_oid_t));
// printf("[DEBUG] osev_osdb:%s user_name:%s\n", authen->auth.osev_osdb, authen->auth.user_name);
char temp[33];
printf("[DEBUG] ObjeConne.m_oid:%s\n", oidstr(temp, &ObjeConne.m_oid));
    printf("    osev clie create ok!\n");
    return 0x00;
}

//

int OSEVClient::Initial() {
    clie_inital_bzl();
    return 0x00;
}

//

int OSEVClient::Cleanup() {
    clie_cleanup_bzl();
    return 0x00;
}

