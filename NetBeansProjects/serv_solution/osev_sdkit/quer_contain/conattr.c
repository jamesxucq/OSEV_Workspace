#include "conattr.h"
#include "cona_list.h"

//
#define CONTA_ATTRIB        "conta_attri.sdo"
#define INVA_INDE_VALU      ((unsigned int)-1)

//

typedef struct {
    osv_oid_t oid;
    char cont_name[CONTA_LENGTH];
    unsigned int stora_type;
    char data_type[CLASS_LENGTH];

    union {
        unsigned int sibling;
        unsigned int recycle;
    };
} conta_attri;

#define INIT_CONTA_ATTR(cattr) \
        memset(&cattr, '\0', sizeof(conta_attri)); \
        cattr.sibling = INVA_INDE_VALU;

//

static FILE *creat_cadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_CONTAIN_FILE(file_name, osdb, CONTA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "wb+");
    if (!attrp) {
        _LOG_ERROR("creat file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}

static FILE *open_cadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_CONTAIN_FILE(file_name, osdb, CONTA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "rb+");
    if (!attrp) {
        _LOG_ERROR("open file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}
#define close_cattr(attrp) fclose(attrp)

//

static int fill_head(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    conta_attri cattr;
    INIT_CONTA_ATTR(cattr)
    if (0 >= fwrite(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int fill_idle(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    conta_attri iattr;
    INIT_CONTA_ATTR(iattr)
    if (0 >= fwrite(&iattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_attri(conta_attri *cattr, FILE *attrp, unsigned int ainde) {
    if (INVA_INDE_VALU == ainde) return -1;
    if (fseeko64(attrp, (__off64_t) ainde * sizeof (conta_attri), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fread(cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}
//

static int modi_sibli(unsigned int sibli, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (conta_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    conta_attri cattr;
    if (0 >= fread(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    cattr.sibling = sibli;
    if (0 >= fwrite(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

#define modi_recycl(recycl, attrp, ainde) modi_sibli(recycl, attrp, ainde)

//

static int activ_attri(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    conta_attri cattr;
    if (0 >= fread(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    modi_sibli(cattr.sibling, attrp, ainde);
    //
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    cattr.sibling = ainde;
    if (0 >= fwrite(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int repla_attri(char *cont_name, uint32 stora_type, char *data_type, osv_oid_t *obje_oid, FILE *attrp, unsigned int rinde) {
    __off64_t eose = (__off64_t) rinde * sizeof (conta_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    conta_attri cattr;
    if (0 >= fread(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    memcpy(&cattr.oid, obje_oid, sizeof (osv_oid_t));
    strcpy(cattr.cont_name, cont_name);
    cattr.stora_type = stora_type;
    strcpy(cattr.data_type, data_type);
    if (0 >= fwrite(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_attr(FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (conta_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(attrp);
    //
    conta_attri iattr;
    if (0 >= fread(&iattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    // printf("iattr.recycle:%x\n", iattr.recycle);
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == iattr.recycle) {
        binde = eose / sizeof (conta_attri);
        printf("get_blank_attr binde:%x\n", binde);
        activ_attri(binde, attrp);
        fill_idle(attrp);
    } else {
        binde = iattr.recycle;
        conta_attri battr;
        if (read_attri(&battr, attrp, binde))
            return INVA_INDE_VALU;
        iattr.recycle = battr.recycle;
        activ_attri(binde, attrp);
        if (fseeko64(attrp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0 >= fwrite(&iattr, sizeof (conta_attri), 0x01, attrp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (conta_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(attrp);
    //
    conta_attri iattr;
    if (0 >= fread(&iattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    modi_recycl(iattr.recycle, attrp, ainde);
    iattr.recycle = ainde;
    if (0 >= fwrite(&iattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_cattr(char *osdb) {
    FILE *attrp = creat_cadat(osdb);
    if (!attrp) return -1;
    fill_head(attrp);
    fill_idle(attrp);
    //
    close_cattr(attrp);
    return 0x00;
}

//

static unsigned int find_inde_name(unsigned int *preind, conta_attri *cattr, FILE *attrp, unsigned int sibli, char *cont_name) {
    conta_attri canod;
    //
    unsigned int cinde = sibli;
    while (!read_attri(&canod, attrp, cinde)) {
        if (!strcmp(cont_name, canod.cont_name)) {
            memcpy(cattr, &canod, sizeof (conta_attri));
            return cinde;
        }
        *preind = cinde;
        cinde = canod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static int find_attr_name(conta_attri *cattr, FILE *attrp, unsigned int sibli, char *cont_name) {
    conta_attri canod;
    //
    canod.sibling = sibli;
    while (!read_attri(&canod, attrp, canod.sibling)) {
        printf("canod.cont_name:%s sibling:%u\n", canod.cont_name, canod.sibling);
        if (!strcmp(cont_name, canod.cont_name)) {
            memcpy(cattr, &canod, sizeof (conta_attri));
            return 0x00;
        }
    }
    //
    return -1;
}

static unsigned int find_attr_type(conta_attri *cattr, FILE *attrp, unsigned int posind, char *data_type) {
    conta_attri canod;
    //
    canod.sibling = posind;
    while (!read_attri(&canod, attrp, canod.sibling)) {
        if (!strcmp(data_type, canod.data_type)) {
            memcpy(cattr, &canod, sizeof (conta_attri));
            return canod.sibling;
        }
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_sibli(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    conta_attri cattr;
    if (0 >= fread(&cattr, sizeof (conta_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return cattr.sibling;
}

//

int addi_cattr(char *cont_name, uint32 stora_type, char *data_type, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    unsigned int binde = get_blank_attr(attrp);
    osv_oid_t obje_oid;
    creat_objeid_obj(&obje_oid);
    // printf("binde:%u\n", binde);
    // printf("stora_type:%u cont_name:%s data_type:%s\n", stora_type, cont_name, data_type);
    repla_attri(cont_name, stora_type, data_type, &obje_oid, attrp, binde);
    //
    close_cattr(attrp);
    return 0x00;
}

//

int dele_cattr(char *cont_name, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    unsigned int sibli = find_sibli(attrp);
    conta_attri cattr;
    unsigned int preind;
    unsigned int ainde = find_inde_name(&preind, &cattr, attrp, sibli, cont_name);
    if (INVA_INDE_VALU != ainde) {
        modi_sibli(cattr.sibling, attrp, preind);
        set_recycled(ainde, attrp);
    }
    //
    close_cattr(attrp);
    return 0x00;
}

//

int find_cattr(osv_oid_t *oid, char *data_type, char *cont_name, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    printf("cont_name:%s\n", cont_name);
    conta_attri cattr;
    if (find_attr_name(&cattr, attrp, 0x00, cont_name)) return -1; // not found
    // found
    memcpy(oid, &cattr.oid, sizeof (osv_oid_t));
    strcpy(data_type, cattr.data_type);
    //
    return 0x00;
}

//

int sear_cattr(char *result, char *osdb, char *cont_name, char *data_type) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    char oid_stri[OID_LINE_LEN];
    conta_attri cattr;
    unsigned int sibli = find_sibli(attrp);
    if (cont_name) {
        if (find_attr_name(&cattr, attrp, sibli, cont_name)) { // not found
            lsprif(result, "Not found contain: %s\n", cont_name);
        } else { // found
            oidstr(oid_stri, &cattr.oid);
            lsprif(result, "contain name:%s class type:%s oid:%s\n", cattr.cont_name, cattr.data_type, oid_stri);
        }
    }
    //
    int found = 0x00;
    unsigned int ainde = sibli;
    if (data_type) {
        while (INVA_INDE_VALU != ainde) {
            ainde = find_attr_type(&cattr, attrp, ainde, data_type);
            if (INVA_INDE_VALU != ainde) { // found
                found = 0x01;
                oidstr(oid_stri, &cattr.oid);
                lsprif(result, "contain name:%s class type:%s oid:%s\n", cattr.cont_name, cattr.data_type, oid_stri);
            } else if (!found) {
                lsprif(result, "Not found class %s contain.\n", data_type);
            }
        }
    }
    //
    close_cattr(attrp);
    return 0x00;
}

//
#define CONVE_CATTR_CONTA(CONTA, OSDB, CANOD) { \
    memcpy(&CONTA->oid, &CANOD.oid, sizeof(osv_oid_t)); \
    strcpy(CONTA->osdb_name, OSDB); \
    strcpy(CONTA->data_type, CANOD.data_type); \
    strcpy(CONTA->cont_name, CANOD.cont_name); \
    CONTA->stora_ha = _storage_ha_[CANOD.stora_type]; \
}

cont_list *load_cattr_osdb(char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return NULL;
    //
    cont_list *colist = NULL;
    contain *conta;
    conta_attri canod;
    // pass head
    if (read_attri(&canod, attrp, 0x00)) return NULL;
    while (!read_attri(&canod, attrp, canod.sibling)) {
        conta = appe_conta(&colist);
        CONVE_CATTR_CONTA(conta, osdb, canod)
    }
    //
    close_cattr(attrp);
    return colist;
}