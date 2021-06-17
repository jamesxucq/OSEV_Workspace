
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "dstr_utili.h"
#include "pinvo.h"
#include "clie_bzl.h"

// SALT_LENGTH

static char *osev_authen_chks(char *chks_str, char *usern, char *paswd, char *salt) {
    char buffe[MID_TEXT_LEN];
    char chks[MD5_TEXT_LENGTH];
    //
    if (!paswd || !usern || !chks_str) return NULL;
    sprintf(buffe, "%s:%s:%s:%s", salt, usern, paswd, salt);
    printf("authen buffe:|%s|\n", buffe);
    get_md5sum_text(buffe, strlen(buffe), chks);
    //
    strncpy(chks_str, chks, PASWD_LENGTH);
    return chks_str;
}

//

int creat_authe_ine(struct authe_ine *auth, char *usern, char *paswd) {
    strcpy(auth->user_name, usern);
    random_salt(auth->salt);
    //
    char salt_buff[SALT_LENGTH + 0x01];
    strzcpy(salt_buff, auth->salt, SALT_LENGTH);
    osev_authen_chks(auth->req_valid, usern, paswd, salt_buff);
    //
    return 0x00;
}

//

int dist_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short colen = encode_dist(pscon->pstyl_str + sizeof (obje_entry), paras);
    if (((unsigned short) - 1) == colen) return -1;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    pscon->colen = colen + sizeof (obje_entry);
    printf("pscon->colen:%d colen:%u\n", pscon->colen, colen);
    return pscon->colen;
}

int ston_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short colen = encode_stri(pscon->pstyl_str + sizeof (obje_entry), paras);
    if (((unsigned short) - 1) == colen) return -1;
    // printf("colen:%d paras[0x00]:%s paras[0x01]:%s\n", colen, paras[0x00], paras[0x01]);
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    // printf("pobje_conte, obsth->enlen:%d\n", obsth->enlen);
    pscon->colen = colen + sizeof (obje_entry);
    //
    return pscon->colen;
}

//

int const_invok_pstyl(osv_pstyl_t *pscon, char **paras) {
    osv_pstyl_t ivkpara;
    quote_decode(paras[0x00]);
    if (-1 == parse_invok_metho(&ivkpara, paras[0x00])) return -1;
    char *last_str = obje_pstyl(pscon->pstyl_str + sizeof (obje_entry), ivkpara.pstyl_str, ivkpara.colen);
    //
    unsigned short enlen = 0x00;
    if (paras[0x01]) {
        enlen = strlen(paras[0x01]) + 0x01;
        stri_pstyl_ex(last_str, paras[0x01], enlen);
        enlen += sizeof (stri_entry);
    }
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = ivkpara.colen + enlen;
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}

//

static osv_str_t INVO_LIST_OBJID = osv_stri("OBJID");
static osv_str_t INVO_LIST_ATTRIB = osv_stri("ATTRIB");
static osv_str_t INVO_LIST_CONTEN = osv_stri("CONTENT");

unsigned int invo_list_type(char *invo_type) {
    if (!invo_type) return LIST_CLAS_ATTRIB | LIST_CLAS_CONTEN;
    quote_decode(invo_type);
    //
    int evalu = 0x00;
    char *delim = strchr(invo_type, '|');
    if (delim) {
        char *last_str = kill_blank(delim + 0x01);
        if (!strncmp(INVO_LIST_ATTRIB.data, last_str, INVO_LIST_ATTRIB.len)) evalu |= LIST_CLAS_ATTRIB;
        else if (!strncmp(INVO_LIST_CONTEN.data, last_str, INVO_LIST_CONTEN.len)) evalu |= LIST_CLAS_CONTEN;
        //
        if (!strncmp(INVO_LIST_ATTRIB.data, invo_type, INVO_LIST_ATTRIB.len)) evalu |= LIST_CLAS_ATTRIB;
        else if (!strncmp(INVO_LIST_CONTEN.data, invo_type, INVO_LIST_CONTEN.len)) evalu |= LIST_CLAS_CONTEN;
    } else {
        if (!strncmp(INVO_LIST_OBJID.data, invo_type, INVO_LIST_OBJID.len)) evalu |= LIST_CLAS_OBJID;
        else if (!strncmp(INVO_LIST_ATTRIB.data, invo_type, INVO_LIST_ATTRIB.len)) evalu |= LIST_CLAS_ATTRIB;
        else if (!strncmp(INVO_LIST_CONTEN.data, invo_type, INVO_LIST_CONTEN.len)) evalu |= LIST_CLAS_CONTEN;
    }
    //
    return evalu;
}

//

int invok_list_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short enlen = 0x00;
    unsigned short colen = strlen(paras[0x00]) + 0x01;
    char *last_str = stri_pstyl_ex(pscon->pstyl_str + sizeof (obje_entry), paras[0x00], colen);
    enlen += sizeof (stri_entry) + colen;
    //
    unsigned int itype = invo_list_type(paras[0x01]);
    uint_pstyl(last_str, itype);
    enlen += PSTY_INT_ELEN;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = enlen;
    pscon->colen = enlen + sizeof (obje_entry);
    //
    return pscon->colen;
}

//

int colle_list_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short enlen = 0x00;
    unsigned short colen = strlen(paras[0x00]) + 0x01;
    char *last_str = stri_pstyl_ex(pscon->pstyl_str + sizeof (obje_entry), paras[0x00], colen);
    enlen += sizeof (stri_entry) + colen;
    //
    unsigned int itype = invo_list_type(paras[0x01]);
    uint_pstyl(last_str, itype);
    enlen += PSTY_INT_ELEN;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = enlen;
    pscon->colen = enlen + sizeof (obje_entry);
    //
    return pscon->colen;
}

//
