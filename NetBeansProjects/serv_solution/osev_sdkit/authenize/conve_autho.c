
#include "privi_obje.h"
#include "conve_autho.h"
#include "priv_utili.h"

//

static char *echo_role_privi(char *last_str, role_privi *role_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(oid_stri, &role_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, role_poin->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == role_poin->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_OSDB == role_poin->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

//

int oconv_role_all(prod_data *sresp, conoda *coval, struct liv_list *role_list) {
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    //
    role_privi *role_poin;
    struct liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSEV == role_poin->role_type)
            last_str = echo_role_privi(last_str, role_poin);
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

static char *echo_dist_privi(char *last_str, dist_privi *priv_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(oid_stri, &priv_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lsprif(last_str, "%08X", priv_poin->privile_mask);
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

int oconv_role_name(prod_data *sresp, conoda *coval, role_privi *role_poin) {
    role_privi role_dat;
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    //
    if (live_load(&role_dat, coval, AUTH_ROLES_CONT, &role_poin->oid))
        return -1;
    last_str = echo_role_privi(last_str, &role_dat);
    //
    int priv_inde;
    dist_privi *priv_poin = role_dat.priv_array;
    for (priv_inde = 0x00; (MAX_PRIVI_SIZE > priv_inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); priv_inde++, priv_poin++) {
        if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi))) {
char oid_stri[OID_LINE_LEN];
printf("--- %s %08X\n", oidstr(oid_stri, &priv_poin->oid), priv_poin->privile_mask);
            mapid_unique(&priv_poin->oid);
            last_str = echo_dist_privi(last_str, priv_poin);
        }
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

//

int dconv_role_name(prod_data *sresp, conoda *coval, role_privi *role_poin) {
    role_privi role_dat;
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    //
    if (live_load(&role_dat, coval, AUTH_ROLES_CONT, &role_poin->oid))
        return -1;
    last_str = echo_role_privi(last_str, &role_dat);
    //
    int priv_inde;
    dist_privi *priv_poin = role_dat.priv_array;
    for (priv_inde = 0x00; (MAX_PRIVI_SIZE > priv_inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); priv_inde++, priv_poin++) {
        if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi))) {
            mapid_unique(&priv_poin->oid);
            last_str = echo_dist_privi(last_str, priv_poin);
        }
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

//

int dconv_role_all(prod_data *sresp, conoda *coval, struct liv_list *role_list) {
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    //
    role_privi *role_poin;
    struct liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSDB == role_poin->role_type)
            last_str = echo_role_privi(last_str, role_poin);
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

//

static char *echo_user_privi(char *last_str, user_privi *user_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(oid_stri, &user_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, user_poin->user_name);
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

void conve_user_all(prod_data *sresp, struct liv_list *ouse_list) {
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    //
    struct liv_list *ulist = ouse_list;
    for (; ulist; ulist = ulist->next) {
        last_str = echo_user_privi(last_str, (user_privi *) ulist->liv_data);
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
}

static char *echo_user_role(char *last_str, role_privi *role_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(oid_stri, &role_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, role_poin->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == role_poin->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_OSDB == role_poin->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

void conve_user_name(prod_data *sresp, user_privi *user_poin) {
    char *last_str = (char *) sresp->sebuf;
    MKZERO(last_str);
    last_str = echo_user_privi(last_str, user_poin);
    //
    role_privi **role_poin = user_poin->role_poin;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && role_poin[0x00]; inde++, role_poin++) {
        if (INVA_POIN_VALU != role_poin[0x00]) {
            last_str = echo_user_role(last_str, role_poin[0x00]);
        }
    }
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
}

//
// #define OSEV_AUTHEN_OFF "OSEV authen is OFF!"
// #define OSEV_AUTHEN_ON "OSEV authen is ON!"

/*
void conve_authen_stat(prod_data *sresp, unsigned int auth_valu) {
    if (auth_valu) lscpy((char *) sresp->sebuf, OSEV_AUTHEN_OFF);
    else lscpy((char *) sresp->sebuf, OSEV_AUTHEN_ON);
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
}
*/