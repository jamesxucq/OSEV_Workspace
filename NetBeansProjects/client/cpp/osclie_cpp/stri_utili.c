
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osev_common/commo_header.h"
#include "stri_utili.h"
#include "pinvo.h"
#include "clie_bzl.h"

//

void get_md5sum_text(char *buf, int len, char *chks_str) {
    MD5_CTX md;

    MD5Init(&md);
    MD5Update(&md, (unsigned char *) buf, len);
    MD5Final(&md);

    uint32 inde;
    for (inde = 0; inde < MD5_DIGEST_LEN; inde++)
        sprintf(chks_str + inde * 2, "%02x", md.digest[inde]);
    chks_str[32] = '\0';
}

char *osev_pass_chks(char *chks_str, char *user_name, char *password) {
    char buffer[MID_TEXT_LEN];
    char chks[MD5_TEXT_LENGTH];
    //
    if (!password || !user_name || !chks_str) return NULL;
    sprintf(buffer, "%s:%s", user_name, password);
    get_md5sum_text(buffer, strlen(buffer), chks);
    //
    strncpy(chks_str, chks, PASSWORD_LENGTH);
    return chks_str;
}

//

int creat_authe(struct authe_ine *auth, char *user, char *pwd) {
    strcpy(auth->user_name, user);
    osev_pass_chks(auth->req_valid, user, pwd);
    return 0x00;
}

//

int para_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short colen = encode_pstyle(pscon->pstyl_str + sizeof (obje_entry), paras);
    if (((unsigned short) - 1) == colen) return -1;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}

int line_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short colen = encode_stri(pscon->pstyl_str + sizeof (obje_entry), paras);
    if (((unsigned short) - 1) == colen) return -1;
    // printf("colen:%d paras[0x00]:%s paras[0x01]:%s\n", colen, paras[0x00], paras[0x01]);
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    // printf("pobje_conte, obsth->enlen:%d\n", obsth->enlen);
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}

int bina_pstyl(osv_pstyl_t *pscon, char **paras, int seri_length) {
    unsigned short colen = encode_obje(pscon->pstyl_str + sizeof (obje_entry), paras, seri_length);
    if (((unsigned short) - 1) == colen) return -1;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    pscon->colen = objen->colen + sizeof (obje_entry);
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

static osv_str_t INVO_ECHO_ATTRIB = osv_stri("ATTRIB");
static osv_str_t INVO_ECHO_CONTEN = osv_stri("CONTENT");

unsigned int invo_echo_type(char *invo_etype) {
    if (!invo_etype) return ECHO_CLAS_ATTRIB | ECHO_CLAS_CONTEN;
    quote_decode(invo_etype);
    //
    int evalu = 0x00;
    char *delim = strchr(invo_etype, '|');
    if (delim) {
        char *last_str = kill_blank(delim + 0x01);
        if (!strncmp(INVO_ECHO_ATTRIB.data, last_str, INVO_ECHO_ATTRIB.len)) evalu |= ECHO_CLAS_ATTRIB;
        else if (!strncmp(INVO_ECHO_CONTEN.data, last_str, INVO_ECHO_CONTEN.len)) evalu |= ECHO_CLAS_CONTEN;
        //
        if (!strncmp(INVO_ECHO_ATTRIB.data, invo_etype, INVO_ECHO_ATTRIB.len)) evalu |= ECHO_CLAS_ATTRIB;
        else if (!strncmp(INVO_ECHO_CONTEN.data, invo_etype, INVO_ECHO_CONTEN.len)) evalu |= ECHO_CLAS_CONTEN;
    } else {
        if (!strncmp(INVO_ECHO_ATTRIB.data, invo_etype, INVO_ECHO_ATTRIB.len)) evalu |= ECHO_CLAS_ATTRIB;
        else if (!strncmp(INVO_ECHO_CONTEN.data, invo_etype, INVO_ECHO_CONTEN.len)) evalu |= ECHO_CLAS_CONTEN;
    }
    //
    return evalu;
}

//

int invok_echo_pstyl(osv_pstyl_t *pscon, char **paras) {
    unsigned short enlen = 0x00;
    unsigned short colen = strlen(paras[0x00]) + 0x01;
    char *last_str = stri_pstyl_ex(pscon->pstyl_str + sizeof (obje_entry), paras[0x00], colen);
    enlen += sizeof (stri_entry) + colen;
    //
    unsigned int nval_uint = invo_echo_type(paras[0x01]);
    uint_pstyl(last_str, nval_uint);
    enlen += PSTY_INT_ELEN;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = enlen;
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}
